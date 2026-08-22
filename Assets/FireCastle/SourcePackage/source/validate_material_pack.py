import json
from pathlib import Path
from PIL import Image

ROOT = Path('/home/ubuntu/FireCastle3D_Pack')
manifest = json.loads((ROOT / 'Materials' / 'material_manifest.json').read_text(encoding='utf-8'))
errors=[]
checked=[]
for item in manifest['texture_sets']:
    for role, filename in item['textures'].items():
        path=ROOT/'Textures'/filename
        if not path.exists() or path.stat().st_size < 512:
            errors.append(f'missing or too small: {filename}')
            continue
        with Image.open(path) as image:
            if image.size != (1024,1024):
                errors.append(f'wrong resolution: {filename} -> {image.size}')
            if role == 'height' and image.mode != 'L':
                errors.append(f'height not grayscale: {filename} -> {image.mode}')
            if role != 'height' and image.mode != 'RGB':
                errors.append(f'map not RGB: {filename} -> {image.mode}')
        checked.append(filename)
fbx = list((ROOT/'StaticMeshes').glob('*.fbx')) + list((ROOT/'SkeletalMeshes').glob('*.fbx'))
glb = list((ROOT/'GLB').glob('*.glb'))
if len(fbx) != 32: errors.append(f'expected 32 FBX files, found {len(fbx)}')
if len(glb) != 32: errors.append(f'expected 32 GLB files, found {len(glb)}')
if not (ROOT/'Source'/'UnrealPython'/'import_fire_castle_materials.py').exists(): errors.append('missing Unreal import script')
report={'texture_sets':len(manifest['texture_sets']),'textures_checked':len(checked),'fbx_checked':len(fbx),'glb_checked':len(glb),'errors':errors,'passed':not errors}
(ROOT/'Documentation'/'material_qa_report.json').write_text(json.dumps(report,ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps(report,ensure_ascii=False))
raise SystemExit(1 if errors else 0)
