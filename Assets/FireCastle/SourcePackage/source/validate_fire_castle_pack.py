import json
import os
import struct
from pathlib import Path

ROOT = Path('/home/ubuntu/FireCastle3D_Pack')
DOC = ROOT / 'Documentation'
manifest = json.loads((DOC / 'asset_manifest.json').read_text(encoding='utf-8'))
results = []
for asset in manifest['assets']:
    fbx = ROOT / asset['fbx']
    glb = ROOT / asset['glb']
    blend = ROOT / asset['blend']
    entry = {'asset': asset['asset'], 'type': asset['type'], 'checks': {}, 'passed': True}
    entry['checks']['fbx_exists_nonzero'] = fbx.exists() and fbx.stat().st_size > 1024
    entry['checks']['blend_exists_nonzero'] = blend.exists() and blend.stat().st_size > 1024
    entry['checks']['glb_exists_nonzero'] = glb.exists() and glb.stat().st_size > 1024
    if entry['checks']['glb_exists_nonzero']:
        header = glb.read_bytes()[:12]
        magic, version, length = struct.unpack('<4sII', header)
        entry['checks']['glb_header_valid'] = magic == b'glTF' and version == 2 and length == glb.stat().st_size
    else:
        entry['checks']['glb_header_valid'] = False
    if entry['checks']['fbx_exists_nonzero']:
        entry['checks']['fbx_binary_signature'] = b'Kaydara FBX Binary' in fbx.read_bytes()[:64]
    else:
        entry['checks']['fbx_binary_signature'] = False
    entry['passed'] = all(entry['checks'].values())
    results.append(entry)

summary = {
    'package': manifest['package'],
    'asset_count_expected': manifest['asset_count'],
    'asset_count_checked': len(results),
    'static_meshes': sum(1 for r in results if r['type'] == 'Static Mesh'),
    'skeletal_meshes': sum(1 for r in results if 'Skeletal' in r['type']),
    'passed': sum(1 for r in results if r['passed']),
    'failed_assets': [r['asset'] for r in results if not r['passed']],
    'checks': results,
}
(DOC / 'qa_report.json').write_text(json.dumps(summary, indent=2, ensure_ascii=False), encoding='utf-8')
print(json.dumps({k: summary[k] for k in ('asset_count_expected','asset_count_checked','static_meshes','skeletal_meshes','passed','failed_assets')}, ensure_ascii=False))
if summary['failed_assets'] or summary['asset_count_expected'] != summary['asset_count_checked']:
    raise SystemExit(1)
