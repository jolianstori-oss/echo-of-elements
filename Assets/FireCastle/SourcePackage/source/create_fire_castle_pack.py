import bpy
import math
import os
import json
from mathutils import Vector

ROOT = "/home/ubuntu/FireCastle3D_Pack"
STATIC_DIR = os.path.join(ROOT, "StaticMeshes")
SKEL_DIR = os.path.join(ROOT, "SkeletalMeshes")
GLB_DIR = os.path.join(ROOT, "GLB")
BLEND_DIR = os.path.join(ROOT, "Source", "Blend")
DOC_DIR = os.path.join(ROOT, "Documentation")
for directory in (STATIC_DIR, SKEL_DIR, GLB_DIR, BLEND_DIR, DOC_DIR):
    os.makedirs(directory, exist_ok=True)

# Game-readable palette: high contrast hazard/interactable materials for the Vertical Slice.
MAT = {}
def mat(name, color, metallic=0.0, roughness=0.65, emission=None):
    material = bpy.data.materials.get(name) or bpy.data.materials.new(name)
    material.use_nodes = True
    material.diffuse_color = (*color, 1.0)
    bsdf = material.node_tree.nodes.get("Principled BSDF")
    bsdf.inputs["Base Color"].default_value = (*color, 1.0)
    bsdf.inputs["Metallic"].default_value = metallic
    bsdf.inputs["Roughness"].default_value = roughness
    if emission:
        bsdf.inputs["Emission Color"].default_value = (*emission, 1.0)
        bsdf.inputs["Emission Strength"].default_value = 2.5
    MAT[name] = material
    return material

OBSIDIAN = mat("M_FC_Obsidian", (0.055, 0.045, 0.06), 0.15, 0.38)
SCORCHED = mat("M_FC_ScorchedStone", (0.13, 0.09, 0.07), 0.05, 0.78)
IRON = mat("M_FC_BurntIron", (0.07, 0.075, 0.08), 0.82, 0.34)
ASH = mat("M_FC_Ash", (0.18, 0.16, 0.15), 0.0, 0.96)
EMBER = mat("M_FC_Ember", (0.9, 0.10, 0.008), 0.10, 0.30, (1.0, 0.035, 0.002))
MAGMA = mat("M_FC_Magma", (1.0, 0.08, 0.003), 0.0, 0.25, (1.0, 0.025, 0.001))
GOLD = mat("M_FC_CinderGold", (0.64, 0.23, 0.02), 0.78, 0.29, (0.7, 0.035, 0.001))
SAFE = mat("M_FC_SafeCyan", (0.015, 0.28, 0.50), 0.15, 0.25, (0.01, 0.4, 1.0))
PURPLE = mat("M_FC_EliteViolet", (0.19, 0.02, 0.31), 0.22, 0.33, (0.38, 0.004, 0.72))
BONE = mat("M_FC_BoneAsh", (0.37, 0.28, 0.20), 0.0, 0.80)
CLOTH = mat("M_FC_CharredCloth", (0.10, 0.018, 0.008), 0.0, 0.90)

EXPORT_RECORDS = []

def clear_scene():
    bpy.ops.object.select_all(action='SELECT')
    bpy.ops.object.delete(use_global=False)
    # Mesh and armature data may be freed between assets; named shared materials remain intact.
    for datablock in (bpy.data.meshes, bpy.data.curves, bpy.data.armatures):
        for item in list(datablock):
            if item.users == 0:
                datablock.remove(item)

def assign_material(obj, material):
    if obj.data and hasattr(obj.data, "materials"):
        obj.data.materials.append(material)

def cube(name, loc, scale, material=OBSIDIAN, bevel=0.0):
    bpy.ops.mesh.primitive_cube_add(location=loc)
    obj = bpy.context.object
    obj.name = name
    obj.dimensions = scale
    bpy.ops.object.transform_apply(location=False, rotation=False, scale=True)
    if bevel:
        modifier = obj.modifiers.new("EdgeSoftening", 'BEVEL')
        modifier.width = bevel
        modifier.segments = 2
        bpy.context.view_layer.objects.active = obj
        bpy.ops.object.modifier_apply(modifier=modifier.name)
    assign_material(obj, material)
    return obj

def cylinder(name, loc, radius, depth, material=OBSIDIAN, vertices=10, rotation=None):
    bpy.ops.mesh.primitive_cylinder_add(vertices=vertices, radius=radius, depth=depth, location=loc, rotation=rotation or (0,0,0))
    obj = bpy.context.object
    obj.name = name
    assign_material(obj, material)
    return obj

def cone(name, loc, radius1, radius2, depth, material=EMBER, vertices=8, rotation=None):
    bpy.ops.mesh.primitive_cone_add(vertices=vertices, radius1=radius1, radius2=radius2, depth=depth, location=loc, rotation=rotation or (0,0,0))
    obj = bpy.context.object
    obj.name = name
    assign_material(obj, material)
    return obj

def sphere(name, loc, radius, material=EMBER, segments=12, rings=6, scale=None):
    bpy.ops.mesh.primitive_uv_sphere_add(segments=segments, ring_count=rings, radius=radius, location=loc)
    obj = bpy.context.object
    obj.name = name
    if scale:
        obj.scale = scale
        bpy.ops.object.transform_apply(location=False, rotation=False, scale=True)
    assign_material(obj, material)
    return obj

def torus(name, loc, major, minor, material=IRON, rotation=None):
    bpy.ops.mesh.primitive_torus_add(major_radius=major, minor_radius=minor, major_segments=16, minor_segments=6, location=loc, rotation=rotation or (0,0,0))
    obj = bpy.context.object
    obj.name = name
    assign_material(obj, material)
    return obj

def rotate(obj, rot):
    obj.rotation_euler = rot
    bpy.context.view_layer.objects.active = obj
    bpy.ops.object.transform_apply(location=False, rotation=False, scale=False)
    return obj

def join_meshes(meshes, name):
    meshes = [m for m in meshes if m and m.type == 'MESH']
    bpy.ops.object.select_all(action='DESELECT')
    for mesh in meshes:
        mesh.select_set(True)
    bpy.context.view_layer.objects.active = meshes[0]
    bpy.ops.object.join()
    joined = bpy.context.object
    joined.name = name
    # Exactly at origin: Unreal places the object from its intended gameplay pivot.
    joined.data.name = name + "_Mesh"
    return joined

def collision_box(asset_name, dimensions, loc=(0,0,0)):
    obj = cube("UCX_" + asset_name + "_00", loc, dimensions, ASH)
    obj.display_type = 'WIRE'
    obj.hide_render = True
    return obj

def select_for_export(objects):
    bpy.ops.object.select_all(action='DESELECT')
    for obj in objects:
        obj.select_set(True)
    bpy.context.view_layer.objects.active = objects[0]

def export_static(asset_name, meshes, collision, category, dimensions_cm, description):
    visual = join_meshes(meshes, asset_name)
    collisions = collision if isinstance(collision, list) else [collision]
    for index, collider in enumerate(collisions):
        collider.name = "UCX_" + asset_name + "_" + str(index).zfill(2)
    # Editable source contains visual mesh + simplified UE collision convention.
    select_for_export([visual] + collisions)
    bpy.ops.wm.save_as_mainfile(filepath=os.path.join(BLEND_DIR, asset_name + ".blend"), check_existing=False)
    bpy.ops.export_scene.fbx(
        filepath=os.path.join(STATIC_DIR, asset_name + ".fbx"),
        use_selection=True, object_types={'MESH'},
        apply_unit_scale=True, apply_scale_options='FBX_SCALE_ALL',
        use_mesh_modifiers=True, mesh_smooth_type='FACE',
        add_leaf_bones=False, bake_anim=False, axis_forward='-Z', axis_up='Y'
    )
    # GLB excludes the UCX helper and is intended for catalog preview / DCC interchange.
    select_for_export([visual])
    bpy.ops.export_scene.gltf(
        filepath=os.path.join(GLB_DIR, asset_name + ".glb"),
        export_format='GLB', use_selection=True, export_apply=True,
        export_materials='EXPORT', export_animations=False, export_yup=True
    )
    EXPORT_RECORDS.append({
        "asset": asset_name, "type": "Static Mesh", "fbx": "StaticMeshes/" + asset_name + ".fbx",
        "glb": "GLB/" + asset_name + ".glb", "blend": "Source/Blend/" + asset_name + ".blend",
        "category": category, "dimensions_cm": dimensions_cm, "description": description,
        "collision": "Embedded UCX box / simplified convex proxy", "pivot": "world origin / base-centre"
    })

def export_skeletal(asset_name, mesh, armature, category, dimensions_cm, description, bones):
    mesh.name = asset_name
    mesh.data.name = asset_name + "_Mesh"
    armature.name = asset_name + "_Skeleton"
    mesh.parent = armature
    select_for_export([mesh, armature])
    bpy.ops.wm.save_as_mainfile(filepath=os.path.join(BLEND_DIR, asset_name + ".blend"), check_existing=False)
    bpy.ops.export_scene.fbx(
        filepath=os.path.join(SKEL_DIR, asset_name + ".fbx"),
        use_selection=True, object_types={'MESH', 'ARMATURE'},
        apply_unit_scale=True, apply_scale_options='FBX_SCALE_ALL', use_mesh_modifiers=True,
        add_leaf_bones=False, bake_anim=False, armature_nodetype='NULL',
        axis_forward='-Z', axis_up='Y'
    )
    select_for_export([mesh, armature])
    bpy.ops.export_scene.gltf(
        filepath=os.path.join(GLB_DIR, asset_name + ".glb"), export_format='GLB',
        use_selection=True, export_apply=True, export_materials='EXPORT',
        export_animations=False, export_yup=True
    )
    EXPORT_RECORDS.append({
        "asset": asset_name, "type": "Skeletal Mesh (prototype)", "fbx": "SkeletalMeshes/" + asset_name + ".fbx",
        "glb": "GLB/" + asset_name + ".glb", "blend": "Source/Blend/" + asset_name + ".blend",
        "category": category, "dimensions_cm": dimensions_cm, "description": description,
        "collision": "Generate Physics Asset in Unreal", "pivot": "world origin / feet at Z=0", "bones": bones,
        "rig_note": "Prototype deformation weights; suitable for retargeting/animation-blockout, not final character animation."
    })

def create_armature(name, height, bone_names):
    bpy.ops.object.armature_add(enter_editmode=True, location=(0,0,0))
    arm = bpy.context.object
    arm.name = name
    arm.data.name = name + "_Data"
    root = arm.data.edit_bones[0]
    root.name = bone_names[0]
    root.head = (0,0,0)
    root.tail = (0,0,max(height * 0.18, 0.35))
    previous = root
    for idx, bone_name in enumerate(bone_names[1:], 1):
        bone = arm.data.edit_bones.new(bone_name)
        z0 = min(height * (0.15 + idx * 0.16), height * 0.84)
        z1 = min(z0 + height * 0.16, height)
        bone.head = (0,0,z0)
        bone.tail = (0,0,z1)
        bone.parent = previous
        bone.use_connect = False
        previous = bone
    bpy.ops.object.mode_set(mode='OBJECT')
    return arm

def skin_mesh(mesh, armature, bones):
    modifier = mesh.modifiers.new("Armature", 'ARMATURE')
    modifier.object = armature
    # Height-weighted prototype skinning establishes a valid bind structure for UE import.
    for bone in bones:
        mesh.vertex_groups.new(name=bone)
    z_values = [vertex.co.z for vertex in mesh.data.vertices]
    zmax = max(z_values) if z_values else 1.0
    for vertex in mesh.data.vertices:
        fraction = max(0.0, min(0.999, vertex.co.z / max(zmax, 0.01)))
        index = min(int(fraction * len(bones)), len(bones)-1)
        mesh.vertex_groups[bones[index]].add([vertex.index], 1.0, 'REPLACE')

def static_floor():
    a=[]
    a.append(cube("Base", (0,0,0.16), (4.0,4.0,0.32), OBSIDIAN, 0.06))
    for x in (-1.28,0,1.28):
        for y in (-1.28,0,1.28):
            tile=cube("Tile", (x,y,0.37), (1.18,1.18,0.09), SCORCHED, 0.025)
            tile.rotation_euler[2]=0.04*(x-y)
            a.append(tile)
    col=collision_box("SM_FC_FloorTile_400", (4.0,4.0,0.40), (0,0,0.20))
    export_static("SM_FC_FloorTile_400", a, col, "Environment / Modular", "400 × 400 × 40", "Obsidian tiled floor with simple modular collision.")

def static_wall():
    a=[cube("WallCore", (0,0,2.0), (4.0,0.50,4.0), OBSIDIAN, 0.04)]
    for z in (0.42,1.18,1.94,2.70,3.46):
        offset=0.0 if int(z*10)%2 else 0.38
        for x in (-1.5+offset,-0.75+offset,0+offset,0.75+offset,1.5+offset):
            if abs(x)<1.85:
                a.append(cube("Brick", (x,-0.28,z), (0.65,0.09,0.62), SCORCHED, 0.02))
    col=collision_box("SM_FC_Wall_400x400", (4.0,0.55,4.0), (0,0,2.0))
    export_static("SM_FC_Wall_400x400", a, col, "Environment / Modular", "400 × 50 × 400", "Scorched masonry wall panel with readable brick silhouette.")

def static_arch():
    a=[]
    for x in (-1.65,1.65):
        a.append(cube("Pier", (x,0,1.35), (0.55,0.75,2.70), SCORCHED, 0.04))
        a.append(cube("PierCap", (x,0,2.78), (0.78,0.94,0.18), OBSIDIAN, 0.02))
    # Keystone blocks approximate a freestanding arch; doorway remains clear below.
    for angle in range(0,181,30):
        r=1.62
        x=r*math.cos(math.radians(angle))
        z=2.60+r*math.sin(math.radians(angle))
        block=cube("ArchStone", (x,0,z), (0.62,0.78,0.38), SCORCHED, 0.03)
        block.rotation_euler[1]=math.radians(90-angle)
        a.append(block)
    col=[collision_box("SM_FC_Archway_400", (0.60,0.85,2.80), (-1.65,0,1.40)), collision_box("SM_FC_Archway_400", (0.60,0.85,2.80), (1.65,0,1.40)), collision_box("SM_FC_Archway_400", (3.80,0.85,0.55), (0,0,4.00))]
    export_static("SM_FC_Archway_400", a, col, "Environment / Modular", "400 × 85 × 425", "Freestanding fire-castle arch with three-part collision that preserves the doorway opening.")

def static_battlement():
    a=[cube("Base", (0,0,0.28), (4,1.2,0.56), SCORCHED, 0.03)]
    for x in (-1.5,-0.5,0.5,1.5):
        a.append(cube("Merlon", (x,0,0.88), (0.62,1.18,0.70), OBSIDIAN, 0.03))
    col=collision_box("SM_FC_Battlement_400", (4,1.2,1.25), (0,0,0.62))
    export_static("SM_FC_Battlement_400", a, col, "Environment / Modular", "400 × 120 × 125", "Parapet module for exterior silhouette and cover.")

def static_pillar():
    a=[cylinder("Base",(0,0,0.16),0.62,0.32,OBSIDIAN), cylinder("Shaft",(0,0,1.8),0.37,3.05,SCORCHED,10), cylinder("Capital",(0,0,3.45),0.66,0.28,OBSIDIAN)]
    for z in (0.85,1.65,2.45):
        a.append(torus("EmberBand",(0,0,z),0.41,0.035,IRON))
    col=collision_box("SM_FC_Pillar_360", (1.35,1.35,3.65), (0,0,1.82))
    export_static("SM_FC_Pillar_360",a,col,"Environment / Modular","135 × 135 × 365","Round modular pillar with iron banding.")

def static_broken_bridge():
    a=[]
    slab_positions=(-3.0,-2.0,-1.0,0.15,1.15,2.15,3.15)
    for x in slab_positions:
        z=0.18 if x<0 else 0.07
        a.append(cube("BridgeSlab",(x,0,z),(0.9,2.4,0.36),SCORCHED,0.06))
    # Intentional traversal gap around x=0.65.
    a.extend([cube("BrokenRail",(-2.1,-1.15,0.75),(2.5,0.12,0.13),IRON), cube("BrokenRail",(2.55,1.15,0.65),(1.75,0.12,0.13),IRON)])
    for x,y in ((-1.5,0.92),(2.5,-0.78),(3.5,0.6)):
        rock=cone("Rubble",(x,y,0.38),0.35,0.05,0.66,SCORCHED,6)
        a.append(rock)
    col=[collision_box("SM_FC_BrokenBridge_800", (0.90,2.4,0.46), (x,0,0.23 if x<0 else 0.14)) for x in slab_positions]
    export_static("SM_FC_BrokenBridge_800",a,col,"Environment / Traversal","800 × 240 × 150","Broken volcanic bridge with separated collision slabs that preserve its intended traversal gap and low rail remnants.")

def static_hot_platform():
    a=[cube("Platform",(0,0,0.18),(4,4,0.36),OBSIDIAN,0.05),cube("Grate",(0,0,0.40),(2.8,2.8,0.06),IRON,0.02)]
    for x in (-0.9,0,0.9):
        a.append(cube("HeatSlit",(x,0,0.45),(0.20,2.3,0.045),MAGMA,0.01))
    col=collision_box("SM_FC_HotPlatform_400", (4,4,0.46), (0,0,0.23))
    export_static("SM_FC_HotPlatform_400",a,col,"Environment / Hazard","400 × 400 × 46","Burning-grate platform; use material and Blueprint state to telegraph active heat.")

def static_fissure():
    a=[cube("LeftStone",(-1.25,0,0.12),(1.5,4,0.24),SCORCHED,0.05),cube("RightStone",(1.25,0,0.12),(1.5,4,0.24),SCORCHED,0.05),cube("MagmaChannel",(0,0,0.15),(0.85,4,0.08),MAGMA,0.01)]
    for y in (-1.35,-0.45,0.45,1.35):
        a.append(cone("MagmaSpurt",(0,y,0.40),0.18,0.02,0.52,EMBER,6))
    col=collision_box("SM_FC_MagmaFissure_400", (4,4,0.30), (0,0,0.15))
    export_static("SM_FC_MagmaFissure_400",a,col,"Environment / Hazard","400 × 400 × 70","Magma fissure visual; drive damage with a separate hazard volume.")

def static_brazier():
    a=[cylinder("Foot",(0,0,0.13),0.55,0.26,IRON,10),cone("Stem",(0,0,0.70),0.22,0.38,0.95,IRON,10),cylinder("Bowl",(0,0,1.24),0.78,0.34,IRON,12),sphere("Core",(0,0,1.40),0.42,MAGMA,10,5,(0.8,0.8,1.2))]
    for angle in (0,120,240):
        x,y=0.72*math.cos(math.radians(angle)),0.72*math.sin(math.radians(angle))
        a.append(cone("Flame",(x,y,1.68),0.17,0.01,0.62,EMBER,6))
    col=collision_box("SM_FC_Brazier", (1.8,1.8,1.95), (0,0,0.98))
    export_static("SM_FC_Brazier",a,col,"Interactive / Boss","180 × 180 × 195","Phase-two boss brazier; use emissive activation state in BP_Brazier.")

def static_shrine():
    a=[cylinder("Step1",(0,0,0.12),1.45,0.24,OBSIDIAN,12),cylinder("Step2",(0,0,0.30),1.05,0.16,SCORCHED,12),cube("Obelisk",(0,0,1.25),(0.48,0.48,1.9),BONE,0.04),sphere("AbsorbCore",(0,0,2.25),0.34,EMBER,10,6)]
    for z,r in ((0.58,0.98),(1.68,0.65)):
        a.append(torus("SigilRing",(0,0,z),r,0.055,GOLD,rotation=(0,0,0)))
    col=collision_box("SM_FC_AbsorbShrine", (3.0,3.0,2.65), (0,0,1.32))
    export_static("SM_FC_AbsorbShrine",a,col,"Interactive / Tutorial","300 × 300 × 265","Absorb tutorial shrine with high-contrast ember core and ring affordance.")

def static_checkpoint():
    a=[cylinder("Base",(0,0,0.12),0.75,0.24,OBSIDIAN,10),cone("Obelisk",(0,0,1.10),0.42,0.14,1.85,SAFE,6),torus("Halo",(0,0,1.52),0.62,0.05,SAFE,rotation=(math.radians(90),0,0))]
    col=collision_box("SM_FC_CheckpointObelisk", (1.6,1.6,2.05), (0,0,1.02))
    export_static("SM_FC_CheckpointObelisk",a,col,"Interactive / Checkpoint","160 × 160 × 205","Blue safe-zone checkpoint obelisk; pair with BP_Checkpoint and particle state.")

def static_door():
    a=[]
    for x in (-1.55,1.55):
        a.append(cube("DoorPillar",(x,0,2.0),(0.55,0.80,4.0),SCORCHED,0.03))
        a.append(cone("DoorFlame",(x,0,4.28),0.20,0.02,0.50,EMBER,6))
    for z in (0.6,1.5,2.4,3.3):
        a.append(cube("Portcullis",(0,0,z),(2.75,0.19,0.11),IRON,0.02))
    a.append(torus("FireSeal",(0,-0.13,2.1),0.75,0.07,EMBER,rotation=(math.radians(90),0,0)))
    col=collision_box("SM_FC_FireGate", (3.8,0.9,4.45), (0,0,2.22))
    export_static("SM_FC_FireGate",a,col,"Interactive / Progression","380 × 90 × 445","Fire-seal portcullis for Gate 01 or encounter locks; animate translate in Blueprint.")

def static_exit_gate():
    a=[cylinder("LeftTower",(-1.65,0,1.8),0.50,3.6,SCORCHED,10),cylinder("RightTower",(1.65,0,1.8),0.50,3.6,SCORCHED,10),torus("ElementRing",(0,0,2.05),1.35,0.14,GOLD,rotation=(math.radians(90),0,0)),sphere("GateCore",(0,0,2.05),1.10,SAFE,16,8,(0.72,0.18,1.0))]
    col=collision_box("SM_FC_ElementalExitGate", (4.2,1.0,4.0), (0,0,2.0))
    export_static("SM_FC_ElementalExitGate",a,col,"Interactive / Exit","420 × 100 × 400","Elemental exit gate with separate glowing core for post-boss transition.")

def static_cinder_key():
    a=[cylinder("KeyBow",(0,0,0.12),0.32,0.12,GOLD,8,rotation=(math.radians(90),0,0)),cube("Shaft",(0.55,0,0),(1.05,0.18,0.18),GOLD,0.02),cube("ToothA",(1.0,0,-0.18),(0.18,0.18,0.30),GOLD,0.01),cube("ToothB",(1.35,0,-0.13),(0.18,0.18,0.22),GOLD,0.01),sphere("Ember",(0,0,0.12),0.16,EMBER,8,4)]
    col=collision_box("SM_FC_CinderKey", (1.8,0.5,0.75), (0.45,0,0.0))
    export_static("SM_FC_CinderKey",a,col,"Pickup / Elite Reward","180 × 50 × 75","Emissive Cinder Key pickup; rotate in BP_CinderKey.")

def static_sigil():
    a=[cylinder("Disc",(0,0,0.10),0.76,0.12,IRON,16),torus("OuterSigil",(0,0,0.18),0.64,0.07,GOLD),torus("InnerSigil",(0,0,0.20),0.32,0.05,EMBER),cone("FlameMark",(0,0,0.42),0.22,0.02,0.46,EMBER,6)]
    col=collision_box("SM_FC_EmberSigil", (1.65,1.65,0.90), (0,0,0.45))
    export_static("SM_FC_EmberSigil",a,col,"Pickup / Boss Reward","165 × 165 × 90","Boss reward sigil with readable fire glyph silhouette.")

def static_lore_pedestal():
    a=[cylinder("Base",(0,0,0.15),0.72,0.30,OBSIDIAN,10),cone("Pedestal",(0,0,0.80),0.52,0.28,1.1,SCORCHED,8),cube("Tablet",(0,0,1.55),(0.68,0.20,0.82),BONE,0.03),sphere("LoreGlow",(0,-0.15,1.72),0.11,SAFE,8,4)]
    col=collision_box("SM_FC_LorePedestal", (1.6,1.6,2.0), (0,0,1.0))
    export_static("SM_FC_LorePedestal",a,col,"Interactive / Optional","160 × 160 × 200","Side-room lore pedestal, visibly distinct from reward pickups.")

def static_reward_chest():
    a=[cube("Chest",(0,0,0.45),(1.35,0.78,0.76),IRON,0.05),cube("Lid",(0,0,0.88),(1.42,0.83,0.22),SCORCHED,0.05),torus("Lock",(0,-0.43,0.60),0.13,0.04,GOLD,rotation=(math.radians(90),0,0))]
    col=collision_box("SM_FC_RewardChest", (1.5,0.9,1.15), (0,0,0.58))
    export_static("SM_FC_RewardChest",a,col,"Interactive / Optional","150 × 90 × 115","Optional reward chest; animate lid in Blueprint.")

def static_rubble():
    a=[]
    pieces=[(-0.65,-0.25,0.18,0.46),(0.05,0.10,0.22,0.62),(0.63,-0.10,0.14,0.35),(-0.05,-0.55,0.12,0.32),(0.42,0.50,0.18,0.40)]
    for idx,(x,y,z,r) in enumerate(pieces):
        rock=cone("Rock"+str(idx),(x,y,z),r,r*0.50,z*2.0,SCORCHED,6)
        rock.rotation_euler=(0.18*idx,0.1*idx,0.4*idx)
        a.append(rock)
    col=collision_box("SM_FC_RubbleCluster", (2.0,1.8,0.8), (0,0,0.4))
    export_static("SM_FC_RubbleCluster",a,col,"Set Dressing","200 × 180 × 80","Low-profile rubble cluster for path guidance without visual obstruction.")

def static_chain():
    a=[]
    for idx,z in enumerate([0.25,0.75,1.25,1.75,2.25]):
        link=torus("ChainLink",(0,0,z),0.23,0.06,IRON,rotation=(math.radians(90),0,0 if idx%2==0 else math.radians(90)))
        if idx%2:
            link.rotation_euler=(0,math.radians(90),0)
        a.append(link)
    col=collision_box("SM_FC_HangingChain", (0.65,0.65,2.7), (0,0,1.35))
    export_static("SM_FC_HangingChain",a,col,"Set Dressing","65 × 65 × 270","Hanging iron chain for furnace halls and exterior dressing.")

def static_stairs():
    a=[]
    for index in range(6):
        a.append(cube("Step"+str(index),(index*0.46,0,0.15+index*0.22),(0.52,2.4,0.30+index*0.22),SCORCHED,0.025))
    col=collision_box("SM_FC_Stair_6Step", (3.0,2.4,1.65), (1.15,0,0.82))
    export_static("SM_FC_Stair_6Step",a,col,"Environment / Modular","300 × 240 × 165","Six-step scorched stone stair module for vertical traversal.")

def static_ceiling():
    a=[cube("Ceiling",(0,0,0),(4,4,0.32),OBSIDIAN,0.04)]
    for x in (-1.2,0,1.2):
        a.append(cube("Rib",(x,0,-0.22),(0.22,4,0.16),IRON,0.02))
    col=collision_box("SM_FC_Ceiling_400", (4,4,0.36), (0,0,0))
    export_static("SM_FC_Ceiling_400",a,col,"Environment / Modular","400 × 400 × 36","Ceiling module for enclosed furnace rooms.")

def static_flame_jet():
    a=[cylinder("Nozzle",(0,0,0.16),0.36,0.32,IRON,10),torus("Rim",(0,0,0.34),0.38,0.055,SCORCHED)]
    for angle in (0,72,144,216,288):
        x,y=0.19*math.cos(math.radians(angle)),0.19*math.sin(math.radians(angle))
        a.append(cone("Flame",(x,y,0.88),0.16,0.015,1.15,EMBER,6))
    col=collision_box("SM_FC_FlameJet", (0.95,0.95,1.8), (0,0,0.9))
    export_static("SM_FC_FlameJet",a,col,"Hazard / VFX Anchor","95 × 95 × 180","Flame-jet nozzle visual; pair with timed damage and Niagara effects.")

def static_heat_barrier():
    a=[cube("FrameL",(-1.3,0,1.5),(0.16,0.20,3.0),IRON,0.02),cube("FrameR",(1.3,0,1.5),(0.16,0.20,3.0),IRON,0.02),cube("FrameTop",(0,0,2.92),(2.76,0.20,0.16),IRON,0.02)]
    for x in (-0.9,-0.45,0,0.45,0.9):
        a.append(cone("HeatColumn",(x,0,1.5),0.16,0.04,2.75,EMBER,6))
    col=collision_box("SM_FC_HeatBarrier", (2.8,0.5,3.0), (0,0,1.5))
    export_static("SM_FC_HeatBarrier",a,col,"Hazard / Progression","280 × 50 × 300","Readable vertical heat barrier for tutorial and resource-gated paths.")

def static_ember_projectile():
    a=[sphere("Core",(0,0,0),0.22,MAGMA,10,6,(1.0,1.0,1.35)),torus("Halo",(0,0,0),0.32,0.035,EMBER,rotation=(math.radians(90),0,0)),cone("Trail",(-0.42,0,0),0.20,0.01,0.75,EMBER,6,rotation=(0,math.radians(-90),0))]
    col=collision_box("SM_FC_EmberProjectile", (1.05,0.65,0.65), (-0.18,0,0))
    export_static("SM_FC_EmberProjectile",a,col,"Gameplay / Projectile","105 × 65 × 65","Absorbable ember projectile visual; forward direction is +X.")

def static_absorb_telegraph():
    a=[torus("Outer",(0,0,0.04),0.85,0.055,EMBER),torus("Inner",(0,0,0.06),0.45,0.035,SAFE),cone("Marker",(0.98,0,0.09),0.10,0.01,0.30,EMBER,4,rotation=(0,math.radians(90),0))]
    col=collision_box("SM_FC_AbsorbTelegraph", (2.1,2.1,0.20), (0,0,0.10))
    export_static("SM_FC_AbsorbTelegraph",a,col,"Gameplay / Telegraph","210 × 210 × 20","Flat timing-ring mesh for Perfect Absorb telegraph; orient on horizontal plane.")

def static_banner():
    a=[cylinder("Pole",(0,0,1.8),0.06,3.6,IRON,8),sphere("Finial",(0,0,3.67),0.14,GOLD,8,4),cube("Cloth",(0.58,0,2.65),(1.18,0.06,1.55),CLOTH,0.02),cone("EmberCrest",(0.58,-0.04,2.70),0.22,0.02,0.48,EMBER,6)]
    col=collision_box("SM_FC_EmberBanner", (1.35,0.45,3.9), (0.28,0,1.95))
    export_static("SM_FC_EmberBanner",a,col,"Set Dressing / Landmark","135 × 45 × 390","Fire-crest banner for route guidance and castle identity.")

# Character factories use intentionally simple, readable silhouettes.  They establish scale, pivot, material slots and a retargetable prototype armature.
def finish_character(asset_name, parts, height, bones, category, dims, desc):
    mesh=join_meshes(parts, asset_name)
    arm=create_armature(asset_name+"_Rig",height,bones)
    skin_mesh(mesh,arm,bones)
    export_skeletal(asset_name,mesh,arm,category,dims,desc,bones)

def char_aren():
    a=[cylinder("LegL",(-0.22,0,0.54),0.16,1.08,IRON,8),cylinder("LegR",(0.22,0,0.54),0.16,1.08,IRON,8),cone("Torso",(0,0,1.42),0.42,0.30,0.86,CLOTH,8),sphere("Head",(0,0,2.07),0.27,BONE,10,6),cube("Sword",(0.57,0,1.23),(0.11,0.18,1.2),IRON,0.01),cube("Guard",(0.57,0,1.72),(0.45,0.14,0.09),GOLD,0.01)]
    finish_character("SK_Aren_Prototype",a,2.4,["root","pelvis","spine","head"],"Characters / Player","110 × 75 × 240","Third-person player scale proxy with armored silhouette and prototype skeleton.")

def char_emberling():
    a=[sphere("Body",(0,0,0.65),0.46,EMBER,10,6,(0.85,0.70,1.15)),sphere("Head",(0.18,0,1.18),0.30,EMBER,10,6),cone("HornL",(0.02,-0.24,1.50),0.13,0.01,0.42,MAGMA,6,rotation=(0,math.radians(-25),0)),cone("HornR",(0.02,0.24,1.50),0.13,0.01,0.42,MAGMA,6,rotation=(0,math.radians(-25),0)),cone("Tail",(-0.50,0,0.62),0.15,0.02,0.72,EMBER,6,rotation=(0,math.radians(70),0)),sphere("EyeL",(0.39,-0.14,1.24),0.05,SAFE,6,3),sphere("EyeR",(0.39,0.14,1.24),0.05,SAFE,6,3)]
    finish_character("SK_Emberling",a,1.7,["root","body","head"],"Enemies / Light","100 × 90 × 170","Small fire imp training enemy; vivid ember silhouette and root/body/head skeleton.")

def char_cinder_caster():
    a=[cone("Robe",(0,0,0.75),0.55,0.27,1.5,CLOTH,8),sphere("Hood",(0,0,1.55),0.34,CLOTH,10,6),sphere("Face",(0.23,0,1.55),0.16,EMBER,8,4),cylinder("Staff",(0,-0.54,1.05),0.06,2.0,BONE,8,rotation=(math.radians(18),0,0)),sphere("StaffCore",(0,-0.84,1.93),0.18,EMBER,8,4)]
    finish_character("SK_CinderCaster",a,2.15,["root","pelvis","spine","head"],"Enemies / Ranged","120 × 120 × 215","Hooded fire caster with staff emissive; distinct ranged silhouette.")

def char_ash_guard():
    a=[cylinder("LegL",(-0.22,0,0.55),0.17,1.10,IRON,8),cylinder("LegR",(0.22,0,0.55),0.17,1.10,IRON,8),cone("Armor",(0,0,1.45),0.52,0.35,0.92,IRON,8),sphere("Helmet",(0,0,2.08),0.32,IRON,10,6),cube("Shield",(0.1,-0.55,1.35),(0.90,0.15,1.15),SCORCHED,0.04),cube("Sword",(0.58,0,1.35),(0.10,0.14,1.40),IRON,0.01),sphere("Visor",(0.30,0,2.08),0.08,EMBER,8,4)]
    finish_character("SK_AshGuard",a,2.45,["root","pelvis","spine","head"],"Enemies / Heavy","145 × 130 × 245","Armored guard, shield and sword silhouette; intended heavy melee archetype.")

def char_warden():
    a=[cylinder("LegL",(-0.36,0,0.72),0.28,1.44,IRON,8),cylinder("LegR",(0.36,0,0.72),0.28,1.44,IRON,8),cone("Torso",(0,0,1.95),0.90,0.54,1.42,PURPLE,8),sphere("Helmet",(0,0,2.96),0.53,IRON,10,6),cylinder("HammerShaft",(0,-0.92,1.70),0.12,2.65,IRON,8,rotation=(math.radians(28),0,0)),cube("HammerHead",(0,-1.55,2.55),(0.66,0.48,0.55),SCORCHED,0.05),sphere("Core",(0.43,0,2.96),0.12,EMBER,8,4)]
    finish_character("SK_EmberWarden",a,3.55,["root","pelvis","spine","head"],"Enemies / Elite","220 × 280 × 355","Large armored elite with hammer and purple/ember phase readability.")

def char_ignar():
    a=[cylinder("LegL",(-0.47,0,0.80),0.34,1.60,IRON,8),cylinder("LegR",(0.47,0,0.80),0.34,1.60,IRON,8),cone("RoyalArmor",(0,0,2.15),1.15,0.65,1.72,OBSIDIAN,10),sphere("Head",(0,0,3.38),0.62,EMBER,12,7),cone("CrownA",(0,0,4.12),0.28,0.02,0.78,GOLD,6),cone("CrownL",(-0.40,0,3.94),0.18,0.02,0.58,GOLD,6),cone("CrownR",(0.40,0,3.94),0.18,0.02,0.58,GOLD,6),cube("FlameBlade",(1.22,0,2.15),(0.18,0.30,2.75),MAGMA,0.03),cube("BladeGuard",(1.22,0,3.33),(0.85,0.22,0.14),IRON,0.02),sphere("HeartCore",(0.66,0,2.25),0.17,MAGMA,8,4)]
    finish_character("SK_Ignar",a,4.55,["root","pelvis","spine","neck","head"],"Enemies / Boss","300 × 175 × 455","King of Embers boss proxy with crown, flame blade and chest core for readable telegraphs.")

def build_all():
    static_builders=[static_floor,static_wall,static_arch,static_battlement,static_pillar,static_broken_bridge,static_hot_platform,static_fissure,static_brazier,static_shrine,static_checkpoint,static_door,static_exit_gate,static_cinder_key,static_sigil,static_lore_pedestal,static_reward_chest,static_rubble,static_chain,static_stairs,static_ceiling,static_flame_jet,static_heat_barrier,static_ember_projectile,static_absorb_telegraph,static_banner]
    char_builders=[char_aren,char_emberling,char_cinder_caster,char_ash_guard,char_warden,char_ignar]
    for builder in static_builders + char_builders:
        clear_scene()
        builder()
    manifest={"package":"Echo of Elements — Fire Castle Prototype 3D Pack","version":"1.0","engine_target":"Unreal Engine 5.8","asset_count":len(EXPORT_RECORDS),"assets":EXPORT_RECORDS}
    with open(os.path.join(DOC_DIR,"asset_manifest.json"),"w",encoding="utf-8") as handle:
        json.dump(manifest,handle,ensure_ascii=False,indent=2)
    print("EXPORTED", len(EXPORT_RECORDS), "ASSETS")
    for item in EXPORT_RECORDS:
        print(item["asset"], item["type"])

if __name__ == "__main__":
    build_all()
