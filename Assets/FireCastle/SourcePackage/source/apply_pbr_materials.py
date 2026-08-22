import bpy
import json
from pathlib import Path

ROOT = Path('/home/ubuntu/FireCastle3D_Pack')
TEXTURE_DIR = ROOT / 'Textures'
BLEND_DIR = ROOT / 'Source' / 'Blend'
STATIC_DIR = ROOT / 'StaticMeshes'
SKEL_DIR = ROOT / 'SkeletalMeshes'
GLB_DIR = ROOT / 'GLB'
manifest = json.loads((ROOT / 'Materials' / 'material_manifest.json').read_text(encoding='utf-8'))
sets = {item['id']: item for item in manifest['texture_sets']}

MAPPING = {
    'M_FC_Obsidian':'Obsidian', 'M_FC_ScorchedStone':'ScorchedBrick', 'M_FC_BurntIron':'BurntIron',
    'M_FC_Ash':'Ash', 'M_FC_Magma':'Magma', 'M_FC_Ember':'Ember', 'M_FC_CinderGold':'CinderGold',
    'M_FC_SafeCyan':'SafeCyan', 'M_FC_EliteViolet':'EliteViolet', 'M_FC_BoneAsh':'BoneAsh',
    'M_FC_CharredCloth':'CharredCloth'
}
EMISSION_STRENGTH = {'Magma':8.0, 'Ember':6.0, 'CinderGold':2.0, 'SafeCyan':3.5, 'EliteViolet':3.5, 'Obsidian':2.6}


def image(name, noncolor=False):
    img = bpy.data.images.load(str(TEXTURE_DIR / name), check_existing=True)
    img.colorspace_settings.name = 'Non-Color' if noncolor else 'sRGB'
    return img


def tex_node(nodes, name, image_name, noncolor=False, location=(0,0)):
    node = nodes.new('ShaderNodeTexImage')
    node.name = name
    node.label = name
    node.image = image(image_name, noncolor)
    node.location = location
    return node


def configure_material(material, material_id):
    data = sets[material_id]
    textures = data['textures']
    material.use_nodes = True
    nodes = material.node_tree.nodes
    links = material.node_tree.links
    nodes.clear()
    output = nodes.new('ShaderNodeOutputMaterial')
    output.location = (900,0)
    bsdf = nodes.new('ShaderNodeBsdfPrincipled')
    bsdf.location = (640,0)
    bsdf.inputs['Specular IOR Level'].default_value = 0.42
    links.new(bsdf.outputs['BSDF'], output.inputs['Surface'])
    coord = nodes.new('ShaderNodeTexCoord')
    coord.location = (-900,0)
    mapping = nodes.new('ShaderNodeMapping')
    mapping.location = (-700,0)
    mapping.inputs['Scale'].default_value = (2.0,2.0,2.0)
    links.new(coord.outputs['Generated'], mapping.inputs['Vector'])
    base = tex_node(nodes, 'Base Color | sRGB', textures['base_color'], False, (-450,280))
    normal = tex_node(nodes, 'Normal | Non-Color', textures['normal'], True, (-450,20))
    orm = tex_node(nodes, 'ORM | Non-Color (R AO / G Roughness / B Metallic)', textures['orm'], True, (-450,-260))
    for node in (base,normal,orm):
        links.new(mapping.outputs['Vector'], node.inputs['Vector'])
    links.new(base.outputs['Color'], bsdf.inputs['Base Color'])
    normal_map = nodes.new('ShaderNodeNormalMap')
    normal_map.location = (180,20)
    normal_map.inputs['Strength'].default_value = 0.75
    links.new(normal.outputs['Color'], normal_map.inputs['Color'])
    links.new(normal_map.outputs['Normal'], bsdf.inputs['Normal'])
    separate = nodes.new('ShaderNodeSeparateRGB')
    separate.location = (180,-260)
    links.new(orm.outputs['Color'], separate.inputs['Image'])
    links.new(separate.outputs['G'], bsdf.inputs['Roughness'])
    links.new(separate.outputs['B'], bsdf.inputs['Metallic'])
    if 'emissive' in textures:
        emit = tex_node(nodes, 'Emissive | sRGB', textures['emissive'], False, (-450,540))
        links.new(mapping.outputs['Vector'], emit.inputs['Vector'])
        links.new(emit.outputs['Color'], bsdf.inputs['Emission Color'])
        bsdf.inputs['Emission Strength'].default_value = EMISSION_STRENGTH.get(material_id, 2.0)
    elif material_id == 'Obsidian':
        # Obsidian crack emission reads during final presentation without obscuring the dark stone base.
        bsdf.inputs['Emission Color'].default_value = (0.55,0.006,0.0,1.0)
        bsdf.inputs['Emission Strength'].default_value = 0.22
    material.diffuse_color = (0.25,0.12,0.04,1.0)


def select_for_export(objects):
    bpy.ops.object.select_all(action='DESELECT')
    for obj in objects:
        obj.select_set(True)
    bpy.context.view_layer.objects.active = objects[0]

for blend_file in sorted(BLEND_DIR.glob('*.blend')):
    asset = blend_file.stem
    bpy.ops.wm.open_mainfile(filepath=str(blend_file))
    configured = 0
    for material in bpy.data.materials:
        if material.name in MAPPING:
            configure_material(material, MAPPING[material.name])
            configured += 1
    visual = bpy.data.objects.get(asset)
    if visual is None:
        raise RuntimeError('Missing visual mesh for ' + asset)
    collisions = [obj for obj in bpy.data.objects if obj.name.startswith('UCX_')]
    armature = visual.parent if visual.parent and visual.parent.type == 'ARMATURE' else None
    # Save editable Blender source with external texture references.
    bpy.ops.wm.save_as_mainfile(filepath=str(blend_file), check_existing=False)
    if asset.startswith('SM_'):
        select_for_export([visual] + collisions)
        bpy.ops.export_scene.fbx(filepath=str(STATIC_DIR / (asset + '.fbx')), use_selection=True, object_types={'MESH'}, apply_unit_scale=True, apply_scale_options='FBX_SCALE_ALL', use_mesh_modifiers=True, mesh_smooth_type='FACE', add_leaf_bones=False, bake_anim=False, axis_forward='-Z', axis_up='Y')
        select_for_export([visual])
    else:
        select_for_export([visual, armature])
        bpy.ops.export_scene.fbx(filepath=str(SKEL_DIR / (asset + '.fbx')), use_selection=True, object_types={'MESH','ARMATURE'}, apply_unit_scale=True, apply_scale_options='FBX_SCALE_ALL', use_mesh_modifiers=True, add_leaf_bones=False, bake_anim=False, armature_nodetype='NULL', axis_forward='-Z', axis_up='Y')
        select_for_export([visual, armature])
    bpy.ops.export_scene.gltf(filepath=str(GLB_DIR / (asset + '.glb')), export_format='GLB', use_selection=True, export_apply=True, export_materials='EXPORT', export_animations=False, export_yup=True)
    print('Applied PBR:', asset, 'materials:', configured)
print('PBR material application complete')
