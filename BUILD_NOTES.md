# Apollo Windows — personal development/testing builds

**Unofficial personal development/testing preview maintained by R3VALATiON.**

This fork and its builds are independent experimental work. They are not official releases of the original Apollo Windows, its Extended fork, Moonlight or Sunshine. No affiliation with, approval by, or endorsement from the upstream maintainers is implied.

Features may be incomplete, unstable or unverified. Build/test status applies only to the exact revision identified with each artifact. Please report fork-specific issues to this personal fork; do not attribute its changes or regressions to the original projects.

Upstream authors retain credit and their original licence terms. These builds are for personal development and testing, not a production-ready release.

## Build labels

Every workflow run, downloaded artifact and build notice is labelled **Personal Development / Testing Preview — UNOFFICIAL**. Future release descriptions must repeat this disclaimer and be marked as pre-releases.

Initial prerelease: [v0.2.0-personal-preview.1](https://github.com/R3VALATiON/Apollo-Extended/releases/tag/v0.2.0-personal-preview.1), with the Windows x64 NSIS installer, changelog, source revision, provenance and SHA-256 checksums.

## Current validation

Native-feedback policy tests, installer PowerShell syntax checks, full Windows compilation and NSIS packaging passed in [GitHub Actions](https://github.com/R3VALATiON/Apollo-Extended/actions/runs/41237024163) for source `5a4198ab9fe108c4cf569308270306e6ce13f0bf`. The installer is attached to the initial prerelease.

Physical controller feedback, native game recognition, connection-quality switching and the matched Windows driver stack have not yet been validated on the user's hardware. Successful compilation is not proof that those hardware paths work.

## Development branch

Prepared implementation: [feature/native-dualsense-adaptive](https://github.com/R3VALATiON/Apollo-Extended/tree/feature/native-dualsense-adaptive).

Native PCM and bandwidth control require the matching personal Artemis/Apollo pair. An upstream binary must not be described as the matching personal build.

## Original project

[Upstream Extended source](https://github.com/Taveszfito/Apollo-Extended). Original authors, acknowledgements and licences remain intact. No upstream pull request is part of this work.
