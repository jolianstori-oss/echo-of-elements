# Run this script inside Unreal Editor's Python console after extracting the package locally.
# Prerequisite: create M_FC_Master_Surface and M_FC_Master_Emissive with the documented texture parameters.
# The script imports PNG maps and creates MI_FC_* instances; it does not replace project gameplay logic.
import json
import os
import unreal

PACKAGE_ROOT = r"C:/Replace/With/FireCastle3D_Pack"  # CHANGE THIS PATH
TEXTURE_SOURCE = os.path.join(PACKAGE_ROOT, "Textures")
MANIFEST_PATH = os.path.join(PACKAGE_ROOT, "Materials", "material_manifest.json")
CONTENT_ROOT = "/Game/EchoOfElements/Stage1/Materials"
MASTER_SURFACE = CONTENT_ROOT + "/M_FC_Master_Surface"
MASTER_EMISSIVE = CONTENT_ROOT + "/M_FC_Master_Emissive"

asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
editor_asset_lib = unreal.EditorAssetLibrary
mat_lib = unreal.MaterialEditingLibrary

def folder_for(texture_role):
    return CONTENT_ROOT + "/Textures/" + texture_role

def import_texture(source_file, destination_path, texture_role):
    asset_name = os.path.splitext(os.path.basename(source_file))[0]
    target = destination_path + "/" + asset_name
    if editor_asset_lib.does_asset_exist(target):
        return unreal.load_asset(target)
    task = unreal.AssetImportTask()
    task.set_editor_property("filename", source_file)
    task.set_editor_property("destination_path", destination_path)
    task.set_editor_property("destination_name", asset_name)
    task.set_editor_property("automated", True)
    task.set_editor_property("save", True)
    task.set_editor_property("replace_existing", False)
    asset_tools.import_asset_tasks([task])
    texture = unreal.load_asset(target)
    if not texture:
        raise RuntimeError("Texture import failed: " + source_file)
    if texture_role in {"normal", "orm", "height"}:
        texture.set_editor_property("srgb", False)
    if texture_role == "normal":
        texture.set_editor_property("compression_settings", unreal.TextureCompressionSettings.TC_NORMALMAP)
    elif texture_role == "orm":
        texture.set_editor_property("compression_settings", unreal.TextureCompressionSettings.TC_MASKS)
    elif texture_role == "height":
        texture.set_editor_property("compression_settings", unreal.TextureCompressionSettings.TC_GRAYSCALE)
    texture.post_edit_change()
    editor_asset_lib.save_asset(target, only_if_is_dirty=True)
    return texture

def create_or_get_instance(instance_name, master):
    path = CONTENT_ROOT + "/Instances/" + instance_name
    if editor_asset_lib.does_asset_exist(path):
        return unreal.load_asset(path)
    factory = unreal.MaterialInstanceConstantFactoryNew()
    instance = asset_tools.create_asset(instance_name, CONTENT_ROOT + "/Instances", unreal.MaterialInstanceConstant, factory)
    instance.set_editor_property("parent", master)
    return instance

with open(MANIFEST_PATH, "r", encoding="utf-8") as file:
    texture_sets = json.load(file)["texture_sets"]

for set_data in texture_sets:
    textures = {}
    for role, filename in set_data["textures"].items():
        textures[role] = import_texture(os.path.join(TEXTURE_SOURCE, filename), folder_for(role), role)
    master_path = MASTER_EMISSIVE if set_data["master_material"] == "M_FC_Master_Emissive" else MASTER_SURFACE
    master = unreal.load_asset(master_path)
    if not master:
        raise RuntimeError("Missing master material: " + master_path)
    instance = create_or_get_instance("MI_FC_" + set_data["id"], master)
    mat_lib.set_material_instance_texture_parameter_value(instance, unreal.Name("T_BaseColor"), textures["base_color"])
    mat_lib.set_material_instance_texture_parameter_value(instance, unreal.Name("T_Normal"), textures["normal"])
    mat_lib.set_material_instance_texture_parameter_value(instance, unreal.Name("T_ORM"), textures["orm"])
    mat_lib.set_material_instance_texture_parameter_value(instance, unreal.Name("T_Height"), textures["height"])
    if "emissive" in textures:
        mat_lib.set_material_instance_texture_parameter_value(instance, unreal.Name("T_Emissive"), textures["emissive"])
        mat_lib.set_material_instance_scalar_parameter_value(instance, unreal.Name("EmissiveIntensity"), 5.0)
    mat_lib.set_material_instance_scalar_parameter_value(instance, unreal.Name("TextureTiling"), 2.0)
    instance.post_edit_change()
    editor_asset_lib.save_asset(instance.get_path_name(), only_if_is_dirty=True)
    unreal.log("Created material instance: " + instance.get_path_name())

unreal.log("Fire Castle material import complete.")
