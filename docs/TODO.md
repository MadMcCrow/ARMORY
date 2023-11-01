# TODO :

# Milestones :

## 0.1 Level Generation
ARMORY is a RTS. As such we must be able to have random maps based on a unique seed and a few parameters

### Setup
- [ ] rethink folder structure
- [ ] NixOS setup
  - [X] build extensions
  - [ ] enable `nix develop` for the game 
  - [ ] build and export game 
- [X] Windows setup
- [ ] Git Hooks

### Docs and design :
- [ ] Write down level logic 
  - [ ] Player bases
  - [ ] Resources
  - [ ] tile set
- [ ] Project management
  - [ ] find a better way to follow progress on milestone
  - [ ] better organise docs (Wiki style)

### Godot :
#### GDScript
- [ ] Level (Maps) should be 
  - [ ] Map scripts as generational (ie. step-based) programming
  - [ ] Map Scripts step as GD Script
  - [ ] Steps are run Async to allow for UI/Wait logic

#### C++
- [X] GridMap as a CPP class
- [X] Tiles are Dict (for now)
- [ ] Poisson distribution

#### UI Design
- [ ] Armory should display a progressbar-like when generating maps

#### Rendering
- [ ] Render tiles with 3D meshes
  - [ ] cubes 