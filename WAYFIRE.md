# Noctalia for Wayfire (`wayfire-extras` branch)

This branch is an **unofficial fork** of [Noctalia](https://github.com/noctalia-dev/noctalia): the [`wayfire`](https://github.com/Nykorin/noctalia/tree/wayfire) branch, which makes the taskbar and dock work properly on [Wayfire](https://github.com/WayfireWM/wayfire), plus two taskbar features that need extra Wayfire plugins. Upstream has decided not to take Wayfire-specific integration, so these changes live here instead.

Please report problems with this branch [on this fork](https://github.com/Nykorin/noctalia/issues), not to Noctalia, whose maintainers don't support it.

## What it changes

From the `wayfire` branch:

- **Minimise from the taskbar and dock.** Clicking a single-window icon minimises the focused window, and restores or focuses it otherwise, as on KDE Plasma and labwc. Noctalia recognises Wayfire, and minimises through `wlr-foreign-toplevel`.
- **Minimise animations aim at the icon.** The taskbar and dock tell the compositor where each window's icon is (`zwlr_foreign_toplevel_handle_v1.set_rectangle`), so Wayfire's minimise animations, such as `squeezimize`, shrink the window into its icon instead of drifting away.

Added on this branch:

- **Window previews in the taskbar.** With the taskbar option `window_preview = true`, hovering an icon shows thumbnails of its windows (up to four for a grouped or pinned icon) instead of the text tooltip. This works on any compositor that offers `ext-foreign-toplevel-image-capture-source-v1`; Wayfire 0.11 doesn't, so it needs the plugin below.
- **Grouping taskbar windows by workspace.** The taskbar's `group_by_workspace` (and `only_active_workspace`, `group_single_icon_per_app`) work on Wayfire, and workspaces show whether they have windows. Each window belongs to the workspace its centre is on, read from Wayfire's IPC.

Everything else is upstream Noctalia, unchanged.

## Requirements

- Wayfire 0.11 or later, with these plugins enabled in `[core] plugins`:
  - `foreign-toplevel`, for minimising from the taskbar and dock.
  - `animate`, with a `minimize_animation` of your choice, for the animation.
  - For window previews: `toplevel-capture` from [wayfire-plugins](https://github.com/Nykorin/wayfire-plugins#toplevel-capture).
  - For grouping by workspace: `ipc` and `ipc-rules`, and a plugin that offers `ext-workspace-v1` for the workspace list. On Wayfire 0.11 that's `ext-workspace-bridge` from [wayfire-plugins](https://github.com/Nykorin/wayfire-plugins#ext-workspace-bridge). From the Wayfire release after 0.11, Wayfire's own `ext-workspace` plugin works too; load only one of the two.
- Noctalia detects Wayfire through `WAYFIRE_SOCKET` or `XDG_CURRENT_DESKTOP`. If you start Noctalia through systemd, make sure those reach it.

Without the extra plugins, the `wayfire` branch's features still work. Previews fall back to the text tooltip, and grouping by workspace doesn't work, so leave `group_by_workspace` off.

## Building and installing

Build it the same way as upstream Noctalia ([BUILDING.md](BUILDING.md)), from this branch:

```sh
git clone -b wayfire-extras https://github.com/Nykorin/noctalia.git
cd noctalia
just configure release
just build release
sudo just install release
```

This installs to `/usr/local`, which comes before `/usr` in `PATH`, so it takes the place of a packaged Noctalia without removing it. Package updates then have no effect until you uninstall this build (`sudo just uninstall release`, run from the same folder).

If you go back to a Noctalia without this branch, turn `group_by_workspace` off first: elsewhere on Wayfire it shows empty workspaces.

## Updating

The branch is kept on top of upstream `main` by rebasing, so its history is rewritten on every update and `git pull` won't work. Update with:

```sh
git fetch origin
git reset --hard origin/wayfire-extras
just build release
sudo just install release
```

`git reset --hard` discards local changes in the clone.

The fork is maintained for as long as its author uses Noctalia on Wayfire.
