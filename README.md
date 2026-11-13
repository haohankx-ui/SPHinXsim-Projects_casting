# ![SPHinXsys Logo](assets/images/logo.png) SPHinXsim Projects

This document explains the purpose of the repository, describes how to set up a project, and gives important guidance on branching, pull requests, and merges.

## Table of Contents
- [What is a SPHinXsim Project?](#what-is-a-sphinxsim-project)
- [How to setup a SPHinXsim Project](#how-to-setup-a-sphinxsim-project)
- [Branching, Pull Requests, and Merging](#branching-pull-requests-and-merging)
- [Contributing to a Project](#contributing-to-a-project)
- [Contributing to SPHinXsim](#contributing-to-sphinxsim)
- [Contributing to SPHinXsys](#contributing-to-sphinxsys)


## What is a SPHinXsim Project?

A **SPHinXsim Project** is a long‑term effort to simulate a complex, multi‑physics problem using SPHinXsim as the simulation environment.

### Ambitious, long‑term goal

A defining feature of such a project is that the ultimate objective is so challenging that there is always something meaningful left to add – more realistic physics, higher accuracy, or additional phenomena. The problem must therefore be an open scientific question (typically multi‑physics) that is under active investigation and will likely remain unsolved for the foreseeable future.

### Co-development with SPHinXsys and SPHinXsim

Another defining characteristic is that the project evolves together with two other projects:

- **SPHinXsys** – provides the numerical solvers as a C++ library.
- **SPHinXsim** – the software framework that lets you assemble and run complex simulations.

Development flows in both directions:

- **Bottom‑up**: new solvers and simulator features enable more physics to be included in the simulation.
- **Top‑down**: the need for new physics drives the creation of new solvers or simulator functionality.

## How to setup a SPHinXsim Project

Each project lives in its own branch, and the branch name must be the project name. All project‑specific files are stored in a directory called `project/` at the repository root. That directory has a fixed internal structure:

1. `extra_src/` – C++ source code that is needed to build the simulation but is not part of the core libraries.
   An umbrella header `sphinxsim_project.h` (or `sphinxsim_project.hpp` for template functions) must be provided; it should include all extra classes and functions.

2. `simulation/` – contains all (2d and 3d) simulation cases. Each case resides in a sub‑folder named after the case. A case folder includes the JSON configuration file and any assets (e.g., geometry files, initial conditions).

3. `docs/` – documentation for the project and auxiliary files (for example, “skills” definitions that enhance AI‑assisted development).

The repository includes a real project (`fish-swimming`) as an example to illustrate how
a project is composed of. However, please **DO NOT** branch your project from there.
You should still branch it from the `main` which already provides an empty template.  

## Branching, Pull Requests, and Merging

Although this repository is a fork of SPHinXsim, we maintain it independently.
Project branches are never pushed back to the upstream SPHinXsim repository.

SPHinXsim is the agent-ready simulation platform for [SPHinXsys](https://github.com/Xiangyu-Hu/SPHinXsys): a structured, automation-friendly interface for building, validating, and running high-fidelity multi-physics simulations.

From a single specification, users and external agents can validate inputs, generate CAD geometry, compile native configurations, launch simulations, and inspect verified results through one consistent CLI and MCP workflow.

### Built for people and autonomous workflows

* JSON-first simulation design with a single source of truth
* Native CLI, shell, and MCP interfaces for interactive and automated use
* CAD-driven geometry generation and validation before execution
* Optional Python integration via pybind11 for embedded workflows
* Visualization and result inspection with [PyVista](https://pyvista.org/)
* Heterogeneous CPU/GPU execution with [SYCL](https://www.khronos.org/sycl/)

### SPHinXsim Agent

The newest workflow makes `sphinxsim` itself the execution layer for both human operators and external agents. There is no separate proprietary agent runtime or cloud-only control plane; the same native application operations are exposed through the shell, the CLI, and the Model Context Protocol (MCP).

This enables powerful agent-driven workflows such as:

* schema validation and simulation input checking,
* CAD generation and geometry review,
* compilation of native simulation configurations,
* persistent execution and job management,
* result inspection and verified resource publication.

For the complete workflow, installation guidance, and MCP configuration, see [Native CLI and external agents](docs/agent-workflows.md).

## Quick start

```bash
python -m pip install -e '.[dev,cad,mcp,results,visualization]'
sphinxsim --help
python -m sphinxsim --help
```

### Interface options

```bash
# Shell / terminal workflow
sphinxsim capabilities --json
sphinxsim validate project/config.json --root /workspace --json

# Python / CLI entry point
python -m sphinxsim --help

# MCP / external agent workflow
sphinxsim mcp --root /workspace
```

## Installation, tutorials, and documentation

SPHinXsim is cross-platform and can be built and used on Windows, Linux, and macOS.

For installation guides, tutorials, and the project manual, visit <https://xiangyu-hu.github.io/SPHinXsim/>.

For native shell usage, CLI workflows, CAD generation, and optional MCP/agent integration, see [Native CLI and external agents](docs/agent-workflows.md).

## Contributing to a Project

There are two ways to contribute to a project:

1. **Directly in the project branch** – if you are a core developer or a collaborator of the project, you can commit directly to the project branch. This is the simplest way to contribute. If you are not a core developer, you can request write access to the project branch from the project maintainers.
2. **Pull requests** – if you are not a core developer, you can fork the repository, create a branch from the project branch, and submit a pull request
to the corresponding project branch main project repository.
The project maintainers will review your changes and merge them into the project branch if they are accepted.

## Contributing to SPHinXsim

If you find that source code in `extra_src` is useful for other projects and you are considering contributing it to the main SPHinXsim repository. 

If you are a core developer or a collaborator of the SPHinXsim, you can commit directly a feature branch to SPHinXsim  in the main SPHinXsim repository and push your changes there without forking SPHinXsim repository. For this, you set the main SPHinXsim repository as a remote and push your changes to it.

#### For academic SPHinXsim users

If you are using SPHinXsim in your research, we would be grateful if you could cite our work in your publications. 
For this, we are happy to help you solve any issues you may encounter with SPHinXsim. Please contact us at <xiangyu.hu@tum.de>.


#### For SPHinXsim developers

It is essential to indicate from which project the contribution origins in the pull request summary. Otherwise the pull requested will not even be reviewed.

### Contributing to SPHinXsys

Again, if you are a core developer or a collaborator of SPHinXsys, you can commit directly to SPHinXsys. For this, you set the main SPHinXsys repository as a remote (different from the one for SPHinXsim).

The SPHinXsys code is embedded inside SPHinXsim at `sphinxsim/sphinxsys`.
You can use `git subtree split` to extract only the changes made in that subdirectory and push them to the SPHinXsys repository.”

Also in this case, please DO NOT try to make pull request from the project branch. The contribution or change needs to be restricted to the `sphinxsim/sphinxsys` folder and be equipped with its own tests and documentation other than those in the project or SPHinXsim. 