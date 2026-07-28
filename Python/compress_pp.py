"""Compress website source PNGs to web-ready WebP.

Folder rules:
    hero       -> long edge 1600, q80
    gallery    -> long edge 1200, q80
    products   -> long edge 800,  q80
    cards      -> long edge 600,  q80
    avatars    -> long edge 400,  q80
    logos      -> no resize, q90 (transparency preserved)
    icons      -> no resize, q90 (transparency preserved)

Aspect ratio preserved; images are only ever downscaled, never upscaled.
Original PNGs remain untouched in ./images.
WebP files are written to ./compressed.
Metadata is not preserved.
"""

import glob
import os

from PIL import Image

SRC = os.path.join(os.getcwd(), "images")
OUT = os.path.join(os.getcwd(), "compressed")

RULES = {
    "hero": {
        "max_edge": 1600,
        "quality": 80,
    },
    "gallery": {
        "max_edge": 1200,
        "quality": 80,
    },
    "products": {
        "max_edge": 800,
        "quality": 80,
    },
    "cards": {
        "max_edge": 600,
        "quality": 80,
    },
    "avatars": {
        "max_edge": 400,
        "quality": 80,
    },
    "logos": {
        "max_edge": None,
        "quality": 90,
    },
    "icons": {
        "max_edge": None,
        "quality": 90,
    },
}


# Create folders if they do not exist. Lazy enough to not create the folders manually
os.makedirs(OUT, exist_ok=True)

for folder in RULES:
    os.makedirs(os.path.join(SRC, folder), exist_ok=True)


DEFAULT_RULE = {
    "max_edge": 800,
    "quality": 80,
}


def human(n: int) -> str:
    for unit in ("B", "KB", "MB"):
        if n < 1024:
            return f"{n:.0f} {unit}"
        n /= 1024
    return f"{n:.1f} GB"


total_before = 0
total_after = 0

patterns = ("*.png", "*.jpg", "*.jpeg", "*.JPG", "*.JPEG", "*.PNG")

paths = []
for pattern in patterns:
    paths.extend(
        glob.glob(os.path.join(SRC, "**", pattern), recursive=True)
    )

for path in sorted(paths):

    relative = os.path.relpath(path, SRC)
    folder = os.path.basename(os.path.dirname(path))

    rule = RULES.get(folder, DEFAULT_RULE)

    max_edge = rule["max_edge"]
    quality = rule["quality"]

    with Image.open(path) as source:

        # Preserve transparency for logos/icons
        if folder in ("logos", "icons"):
            img = source.convert("RGBA")        #trans shit
        else:
            img = source.convert("RGB")

    w, h = img.size

    # Only downscale
    if max_edge:
        scale = min(1.0, max_edge / max(w, h))

        if scale < 1.0:
            img = img.resize(
                (round(w * scale), round(h * scale)),
                Image.LANCZOS
            )

    output_path = os.path.splitext(relative)[0] + ".webp"
    out = os.path.join(OUT, output_path)

    os.makedirs(os.path.dirname(out), exist_ok=True)

    img.save(
        out,
        "WEBP",
        quality=quality,
        method=6
    )

    before = os.path.getsize(path)
    after = os.path.getsize(out)

    total_before += before
    total_after += after

    print(
        f"{relative:45s} "
        f"[{folder:10s}] "
        f"{w}x{h} {human(before):>8s}"
        f" -> "
        f"{img.size[0]}x{img.size[1]} {human(after):>8s}"
    )


print("-" * 95)

if total_before:
    print(
        f"{'TOTAL':45s}"
        f"{human(total_before):>10s}"
        f" -> "
        f"{human(total_after):>10s}"
        f"   "
        f"({100 * (1 - total_after / total_before):.0f}% smaller)"
    )
else:
    print("No PNG files found.")