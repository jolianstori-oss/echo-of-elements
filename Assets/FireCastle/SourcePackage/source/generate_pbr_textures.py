import json
import math
from pathlib import Path

import numpy as np
from PIL import Image

ROOT = Path('/home/ubuntu/FireCastle3D_Pack')
OUT = ROOT / 'Textures'
OUT.mkdir(exist_ok=True)
SIZE = 1024
rng = np.random.default_rng(8027)

# Colour tuples are linear art-direction targets, converted to 8-bit at write time.
MATERIALS = [
    {'id':'Obsidian','label':'Obsidian Fracture','kind':'obsidian','metal':0.10,'rough':0.30,'emissive':False},
    {'id':'ScorchedBrick','label':'Scorched Furnace Brick','kind':'brick','metal':0.02,'rough':0.82,'emissive':False},
    {'id':'BurntIron','label':'Oxidised Burnt Iron','kind':'iron','metal':0.90,'rough':0.42,'emissive':False},
    {'id':'Ash','label':'Volcanic Ash','kind':'ash','metal':0.00,'rough':0.96,'emissive':False},
    {'id':'Magma','label':'Flowing Magma','kind':'magma','metal':0.00,'rough':0.30,'emissive':True},
    {'id':'Ember','label':'Ember Core','kind':'ember','metal':0.03,'rough':0.28,'emissive':True},
    {'id':'CinderGold','label':'Cinder Gold','kind':'gold','metal':0.82,'rough':0.31,'emissive':True},
    {'id':'SafeCyan','label':'Aether Safe Cyan','kind':'cyan','metal':0.30,'rough':0.24,'emissive':True},
    {'id':'EliteViolet','label':'Elite Violet','kind':'violet','metal':0.25,'rough':0.36,'emissive':True},
    {'id':'BoneAsh','label':'Ashen Bone Stone','kind':'bone','metal':0.00,'rough':0.76,'emissive':False},
    {'id':'CharredCloth','label':'Charred Cloth','kind':'cloth','metal':0.00,'rough':0.90,'emissive':False},
]

Y, X = np.mgrid[0:SIZE, 0:SIZE].astype(np.float32)
U = X / SIZE
V = Y / SIZE


def clamp(x):
    return np.clip(x, 0.0, 1.0)


def smoothstep(a, b, x):
    t = clamp((x-a) / max(b-a, 1e-6))
    return t*t*(3.0-2.0*t)


def periodic_noise(seed, octaves=5):
    local = np.random.default_rng(seed)
    field = np.zeros((SIZE, SIZE), dtype=np.float32)
    weight = 0.0
    for octave in range(octaves):
        frequency = 2 ** octave
        amplitude = 1.0 / (2 ** (octave * 0.62))
        # Finite Fourier series is inherently tileable at every image border.
        for _ in range(5):
            fx = local.integers(1, frequency + 2)
            fy = local.integers(1, frequency + 2)
            phase = local.random() * math.tau
            field += amplitude * np.sin(math.tau * (fx * U + fy * V) + phase)
        weight += 5 * amplitude
    field = field / weight
    return clamp(field * 0.5 + 0.5)


def normal_from_height(height, strength=4.0):
    dx = np.roll(height, -1, axis=1) - np.roll(height, 1, axis=1)
    dy = np.roll(height, -1, axis=0) - np.roll(height, 1, axis=0)
    nx, ny, nz = -dx * strength, -dy * strength, np.ones_like(height)
    length = np.sqrt(nx*nx + ny*ny + nz*nz)
    normal = np.dstack((nx/length, ny/length, nz/length))
    return (clamp(normal * 0.5 + 0.5) * 255).astype(np.uint8)


def colorize(a, low, high):
    lo = np.array(low, dtype=np.float32)
    hi = np.array(high, dtype=np.float32)
    return clamp(lo + a[..., None] * (hi - lo))


def make_material(spec, index):
    n1 = periodic_noise(100 + index * 17, 5)
    n2 = periodic_noise(500 + index * 19, 7)
    fine = periodic_noise(900 + index * 23, 8)
    kind = spec['kind']
    emission = np.zeros((SIZE, SIZE, 3), dtype=np.float32)

    if kind == 'obsidian':
        ridge = np.abs(np.sin(math.tau * (3.0*U + 1.0*V + 0.12*n1)) * np.sin(math.tau * (1.0*U - 4.0*V + 0.18*n2)))
        cracks = 1.0 - smoothstep(0.045, 0.12, ridge)
        height = clamp(0.45*n1 + 0.35*n2 + 0.20*fine - 0.42*cracks)
        bc = colorize(height, (0.012,0.008,0.017), (0.13,0.09,0.18))
        emission = np.dstack((cracks*0.95, cracks*0.045, cracks*0.003))
        rough = clamp(0.18 + 0.30*n2 + 0.20*cracks)
    elif kind == 'brick':
        rows = 7.0
        yy = (V * rows) % 1.0
        row = np.floor(V * rows).astype(int)
        xx = (U * 5.2 + 0.5*(row % 2)) % 1.0
        mortar = np.maximum(1.0 - smoothstep(0.035, 0.085, np.minimum(xx, 1-xx)), 1.0 - smoothstep(0.045,0.10,np.minimum(yy,1-yy)))
        height = clamp(0.56 + 0.30*n1 + 0.14*fine - 0.55*mortar)
        bc = colorize(height, (0.095,0.030,0.012), (0.32,0.095,0.035))
        soot = smoothstep(0.62,0.94,n2)
        bc *= (1.0 - soot[...,None]*0.45)
        rough = clamp(0.68 + 0.22*n2 + mortar*0.15)
    elif kind == 'iron':
        bands = 0.5 + 0.5*np.sin(math.tau*(V*34 + n1*0.8))
        pitting = smoothstep(0.66,0.92,n2)
        height = clamp(0.42*n1 + 0.30*bands + 0.28*fine - pitting*0.38)
        bc = colorize(height, (0.025,0.030,0.037), (0.19,0.21,0.24))
        rust = smoothstep(0.73,0.91,n1*n2)
        bc = bc*(1-rust[...,None]*0.65) + np.array((0.22,0.035,0.005))*rust[...,None]
        rough = clamp(0.28 + 0.32*n2 + rust*0.42)
    elif kind == 'ash':
        dunes = 0.5+0.5*np.sin(math.tau*(V*5+n1*1.8))
        height = clamp(0.44*n1 + 0.26*n2 + 0.30*dunes)
        bc = colorize(height, (0.055,0.046,0.043), (0.24,0.21,0.19))
        rough = clamp(0.82 + 0.16*fine)
    elif kind == 'magma':
        flow = np.sin(math.tau*(U*3 + 0.55*np.sin(math.tau*V*2) + n1*1.25))
        veins = smoothstep(0.54,0.77,flow*0.5+0.5)
        height = clamp(0.35*n1 + 0.25*n2 + 0.40*veins)
        bc = colorize(height, (0.10,0.001,0.000), (1.0,0.18,0.002))
        emission = bc * (0.75 + 0.25*veins[...,None])
        rough = clamp(0.15 + 0.20*(1-veins))
    elif kind == 'ember':
        core = smoothstep(0.35,0.80,n1*0.55+n2*0.45)
        height = clamp(0.28*n1 + 0.32*n2 + 0.40*core)
        bc = colorize(height, (0.18,0.003,0.000), (1.0,0.16,0.002))
        emission = colorize(core, (0.28,0.002,0.000), (1.0,0.07,0.001))
        rough = clamp(0.18 + 0.25*n2)
    elif kind == 'gold':
        height = clamp(0.48*n1 + 0.18*n2 + 0.34*(0.5+0.5*np.sin(math.tau*V*30)))
        bc = colorize(height, (0.17,0.025,0.002), (0.95,0.39,0.015))
        emission = colorize(smoothstep(0.70,0.95,n2), (0,0,0), (0.48,0.024,0.001))
        rough = clamp(0.20 + 0.22*n2)
    elif kind == 'cyan':
        circuit = 1.0-smoothstep(0.025,0.08,np.abs(np.sin(math.tau*(3*U+2*V+n1*0.25))))
        height = clamp(0.50*n1 + 0.20*n2 + 0.30*circuit)
        bc = colorize(height, (0.001,0.025,0.06), (0.02,0.42,0.90))
        emission = colorize(circuit, (0.0,0.01,0.04), (0.01,0.78,1.0))
        rough = clamp(0.16 + 0.22*n2)
    elif kind == 'violet':
        channels = smoothstep(0.76,0.91,n1*n2)
        height = clamp(0.44*n1 + 0.32*n2 + 0.24*fine)
        bc = colorize(height, (0.035,0.002,0.08), (0.32,0.006,0.58))
        emission = colorize(channels, (0,0,0), (0.45,0.003,1.0))
        rough = clamp(0.25 + 0.28*n2)
    elif kind == 'bone':
        striations = 0.5 + 0.5*np.sin(math.tau*(V*18+n1*1.1))
        height = clamp(0.42*n1+0.25*n2+0.33*striations)
        bc = colorize(height, (0.09,0.055,0.026), (0.50,0.34,0.19))
        rough = clamp(0.60+0.25*n2)
    elif kind == 'cloth':
        warp = 0.5+0.5*np.sin(math.tau*U*46)
        weft = 0.5+0.5*np.sin(math.tau*V*46)
        weave = warp*weft
        height = clamp(0.60*weave+0.20*n1+0.20*fine)
        bc = colorize(height, (0.008,0.001,0.001), (0.13,0.010,0.003))
        rough = clamp(0.82+0.12*n2)
    else:
        raise ValueError(kind)

    ao = clamp(0.45 + 0.55*height)
    orm = np.dstack((ao, rough, np.full_like(height, spec['metal'])))
    return bc, normal_from_height(height, 5.0 if kind in {'obsidian','brick'} else 3.2), orm, emission, height


def save_rgb(path, arr):
    Image.fromarray((clamp(arr)*255).astype(np.uint8), mode='RGB').save(path, optimize=True)

manifest = {'package':'Fire Castle Final Materials','resolution':SIZE,'texture_sets':[]}
for index, spec in enumerate(MATERIALS):
    bc, normal, orm, emission, height = make_material(spec, index)
    prefix = 'T_FC_' + spec['id']
    bc_file = prefix + '_BC.png'
    n_file = prefix + '_N.png'
    orm_file = prefix + '_ORM.png'
    h_file = prefix + '_H.png'
    save_rgb(OUT / bc_file, bc)
    Image.fromarray(normal, mode='RGB').save(OUT / n_file, optimize=True)
    save_rgb(OUT / orm_file, orm)
    Image.fromarray((clamp(height)*255).astype(np.uint8), mode='L').save(OUT / h_file, optimize=True)
    texture_set = {
        'id': spec['id'], 'label': spec['label'], 'master_material': 'M_FC_Master_Emissive' if spec['emissive'] else 'M_FC_Master_Surface',
        'textures': {'base_color':bc_file,'normal':n_file,'orm':orm_file,'height':h_file},
        'ue_settings': {'base_color':'sRGB true','normal':'sRGB false; Compression: Normalmap','orm':'sRGB false; Compression: Masks (R=AO,G=Roughness,B=Metallic)','height':'sRGB false; Compression: Grayscale'},
        'parameters': {'metallic':spec['metal'],'roughness_art_direction':spec['rough'],'emissive':spec['emissive']}
    }
    if spec['emissive']:
        e_file = prefix + '_E.png'
        save_rgb(OUT / e_file, emission)
        texture_set['textures']['emissive'] = e_file
        texture_set['ue_settings']['emissive'] = 'sRGB true; use as emissive color, expose EmissiveIntensity scalar'
    manifest['texture_sets'].append(texture_set)

(ROOT / 'Materials' / 'material_manifest.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2), encoding='utf-8')
print('Generated', len(MATERIALS), 'PBR texture sets at', SIZE, 'px')
