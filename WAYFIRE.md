# Noctalia for Wayfire (`wayfire` branch)

This branch is an **unofficial fork** of [Noctalia](https://github.com/noctalia-dev/noctalia): upstream `main` plus two commits that make [Wayfire](https://github.com/WayfireWM/wayfire)'s minimise animations aim at the taskbar and dock icons. Upstream has decided not to take Wayfire-specific integration, so these changes live here instead.

Please report problems with this branch [on this fork](https://github.com/Nykorin/noctalia/issues), not to Noctalia, whose maintainers don't support it.

## What it changes

- **Minimise animations aim at the icon.** The taskbar and dock tell the compositor where each window's icon is (`zwlr_foreign_toplevel_handle_v1.set_rectangle`), so Wayfire's minimise animations, such as `squeezimize`, shrink the window into its icon instead of drifting away.

Everything else is upstream Noctalia, unchanged. Minimising from the taskbar and dock is part of upstream Noctalia itself: Wayfire is a compositor Noctalia doesn't recognise, and on those it minimises through `wlr-foreign-toplevel`.

## Requirements

- Wayfire 0.11 or later, with these plugins enabled in `[core] plugins`:
  - `foreign-toplevel`, which minimising and the icon positions go through.
  - `animate`, with a `minimize_animation` of your choice, for the animation.

## Building and installing

Build it the same way as upstream Noctalia ([BUILDING.md](BUILDING.md)), from this branch:

```sh
git clone -b wayfire https://github.com/Nykorin/noctalia.git
cd noctalia
just configure release
just build release
sudo just install release
```

This installs to `/usr/local`, which comes before `/usr` in `PATH`, so it takes the place of a packaged Noctalia without removing it. Package updates then have no effect until you uninstall this build (`sudo just uninstall release`, run from the same folder).

## Updating

The branch is kept on top of upstream `main` by rebasing, so its history is rewritten on every update and `git pull` won't work. Update with:

```sh
git fetch origin
git reset --hard origin/wayfire
just build release
sudo just install release
```

`git reset --hard` discards local changes in the clone.

## Other branches

- [`wayfire-extras`](https://github.com/Nykorin/noctalia/tree/wayfire-extras): this branch plus window previews in taskbar tooltips and grouping taskbar windows by workspace, which need extra Wayfire plugins.

The fork is maintained for as long as its author uses Noctalia on Wayfire.
