# Test Assignment

## Objective
Create a shared library and a CLI utility that:

1. Retrieves lists of binary packages from two branches (e.g., sisyphus and p10) using the public REST API: [https://rdb.altlinux.org/api/](https://rdb.altlinux.org/api/). The method to use is `/export/branch_binary_packages/{branch}` where `{branch}` can be sisyphus, p10, p9, etc.
2. Compares the lists of packages and outputs a JSON structure showing:
   - All packages that are present in the first branch but not in the second.
   - All packages that are present in the second branch but not in the first.
   - All packages where the `version-release` is higher in the first branch than in the second.

The comparison should be performed for each supported architecture (field `arch` in the response).

## Requirements
- The shared library should be built following these recommendations: [Program Library HOWTO: Shared Libraries](https://tldp.org/HOWTO/Program-Library-HOWTO/shared-libraries.html)
- The development process should be documented with a git repository, showing the history of changes from the very first step (without rewriting commits) and published on GitHub.

## Development Tools
- Any necessary libraries can be used, provided they are available from the ALT Linux repository: [ALT Linux Packages](https://packages.altlinux.org/ru/p10/).

## Deliverables
- A README in English containing:
  - Instructions for installing the utility in the system (according to the FHS standard).
  - Instructions for running the utility.
- The utility should run on Linux (it will be tested on ALT Workstation K 10.1).

## Instructions for Running the Utility
- Ensure that the utility runs under ALT Workstation K 10.1.