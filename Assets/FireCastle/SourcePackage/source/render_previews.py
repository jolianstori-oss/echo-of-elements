import bpy
import os
from mathutils import Vector

ROOT='/home/ubuntu/FireCastle3D_Pack'
BLEND=os.path.join(ROOT,'Source','Blend')
OUT=os.path.join(ROOT,'Previews')
os.makedirs(OUT,exist_ok=True)
SAMPLES=['SM_FC_AbsorbShrine','SM_FC_FireGate','SM_FC_BrokenBridge_800','SK_Emberling','SK_EmberWarden','SK_Ignar']

def bounds_of(objects):
    corners=[]
    for obj in objects:
        if obj.type == 'MESH' and not obj.name.startswith('UCX_'):
            corners += [obj.matrix_world @ Vector(c) for c in obj.bound_box]
    lo=Vector((min(v.x for v in corners),min(v.y for v in corners),min(v.z for v in corners)))
    hi=Vector((max(v.x for v in corners),max(v.y for v in corners),max(v.z for v in corners)))
    return lo,hi

def look_at(obj, target):
    obj.rotation_euler=(Vector(target)-obj.location).to_track_quat('-Z','Y').to_euler()

for asset in SAMPLES:
    bpy.ops.wm.open_mainfile(filepath=os.path.join(BLEND,asset+'.blend'))
    scene=bpy.context.scene
    scene.render.engine='BLENDER_EEVEE'
    scene.world.color=(0.012,0.012,0.018)
    scene.view_settings.look='AgX - Medium High Contrast'
    scene.render.resolution_x=512
    scene.render.resolution_y=512
    scene.render.resolution_percentage=100
    scene.render.image_settings.file_format='PNG'
    scene.render.film_transparent=False
    for obj in list(bpy.data.objects):
        if obj.type in {'CAMERA','LIGHT'}:
            bpy.data.objects.remove(obj,do_unlink=True)
    lo,hi=bounds_of(bpy.context.scene.objects)
    center=(lo+hi)*0.5
    size=max((hi-lo).x,(hi-lo).y,(hi-lo).z)
    bpy.ops.object.camera_add(location=(center.x+size*1.55,center.y-size*1.55,center.z+size*0.90))
    camera=bpy.context.object
    camera.data.lens=52
    look_at(camera,center)
    scene.camera=camera
    bpy.ops.object.light_add(type='AREA',location=(center.x+size,center.y-size,center.z+size*1.6))
    key=bpy.context.object
    key.data.energy=1500
    key.data.shape='DISK'
    key.data.size=max(size*2,1)
    look_at(key,center)
    scene.render.filepath=os.path.join(OUT,asset+'.png')
    bpy.ops.render.render(write_still=True)
    print('Rendered',asset)
