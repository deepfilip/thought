# Thought Wallet / Thought Core 0.18.4

## 🍎 Updated macOS Apple Silicon release

**Looking for the Mac version? This fork contains the macOS-specific maintenance, release hardening, and packaging work used to provide a working Apple Silicon (arm64) community build of Thought Wallet / Thought Core 0.18.4.**

[![Download for macOS Apple Silicon](https://img.shields.io/badge/Download_for_macOS-Apple_Silicon_arm64-000000?style=for-the-badge&logo=apple&logoColor=white)](https://github.com/deepfilip/thought/releases/download/v0.18.4-community-r3/Thought-Wallet-0.18.4-macOS-arm64-community-adhoc-r3.dmg)

**Current release:** [Thought Wallet 0.18.4 — macOS arm64 Community Build R3](https://github.com/deepfilip/thought/releases/tag/v0.18.4-community-r3)  
**Direct DMG:** [`Thought-Wallet-0.18.4-macOS-arm64-community-adhoc-r3.dmg`](https://github.com/deepfilip/thought/releases/download/v0.18.4-community-r3/Thought-Wallet-0.18.4-macOS-arm64-community-adhoc-r3.dmg)  
**DMG SHA-256:** `656a8b69dc7bff05b6d93e799fc4daf49b2f74f7123a8ca2a8e42c779e7d6f4d`

> **Important:** This is a community-maintained macOS build. It is ad-hoc signed and not Apple-notarized, and it should not be interpreted as an official upstream Thought Network release or as Apple-endorsed software.

## ⚡ Fast initial blockchain sync

A brand-new wallet may otherwise need to synchronize years of Thought blockchain history from peers. The optional [fast-sync guide](doc/macos-fast-sync.md) documents a maintainer-hosted Thought chain snapshot and the associated trust/rollback precautions.

The exact macOS snapshot compatibility test recorded by this repository was performed with Community Build R2 on 10 September 2026. R3 is the current application release; that R2 test remains historical evidence and is not represented as a separate R3 snapshot-compatibility requalification.

## What this Mac release contains

The current community release provides:

- `Thought-Wallet-0.18.4-macOS-arm64-community-adhoc-r3.dmg` — the macOS Apple Silicon application disk image;
- `SHA256SUMS.txt` — published SHA-256 checksums;
- `Thought-Wallet-0.18.4-macOS-arm64-community-source-compliance-r3.tar.gz` — the source-compliance companion archive.

Verify the downloaded DMG's SHA-256 before opening it.

## About this repository

This repository is a community-maintained fork of [`thoughtnetwork/thought`](https://github.com/thoughtnetwork/thought) used to maintain and publish the macOS Apple Silicon (arm64) community release of Thought Wallet / Thought Core 0.18.4.

Thought is an experimental peer-to-peer digital currency. The upstream project website is [thought.live](https://thought.live).

## Documentation map

- **Install/build entry point:** [`INSTALL.md`](INSTALL.md)
- **macOS Apple Silicon build and reproduction:** [`doc/macos-arm64-build.md`](doc/macos-arm64-build.md)
- **Fast initial sync on macOS:** [`doc/macos-fast-sync.md`](doc/macos-fast-sync.md)
- **Generic depends-based build flow:** [`doc/build-generic.md`](doc/build-generic.md)
- **Inherited legacy macOS notes:** [`doc/build-osx.md`](doc/build-osx.md)
- **Contributor workflow:** [`CONTRIBUTING.md`](CONTRIBUTING.md)

The Apple Silicon guide distinguishes what is verified for the published R3 release from what remains environment-dependent in a fresh source build. The R3 release does **not** claim full historical build reproducibility.

## Release checksums

| File | SHA-256 |
| --- | --- |
| `Thought-Wallet-0.18.4-macOS-arm64-community-adhoc-r3.dmg` | `656a8b69dc7bff05b6d93e799fc4daf49b2f74f7123a8ca2a8e42c779e7d6f4d` |
| `Thought-Wallet-0.18.4-macOS-arm64-community-source-compliance-r3.tar.gz` | `298d4df93e8fab297f29a231f36f418b56c9c955d7080718f92ca11a6f0cbc9c` |
| `SHA256SUMS.txt` | `89f591b92e6d3756380376513c89650e0fc38fa09d6ecbbed8fe2fd448ec1cce` |

## macOS security notice

The macOS community build is **ad-hoc signed and not Apple-notarized**. It is not signed with an Apple Developer ID certificate.

Because of that distribution model, macOS may block the first launch and report that Apple cannot check the application for malicious software. After verifying the download and only if you trust it, macOS provides an **Open Anyway** control under **System Settings → Privacy & Security** following an initial blocked launch attempt.

Do **not** disable Gatekeeper globally.

The exact R3 qualification path was same-host and did not carry a quarantine attribute, so a fresh downloaded-file Gatekeeper first-open path was not independently re-proven for R3. See the R3 release limitations for the exact scope.

## First launch

The R3 functional launch qualification used bounded disposable REGTEST controls. Default fresh-wallet first-launch performance was not adjudicated by that test and should not be inferred from it.

## Support and bug reports

For reproducible problems with this **community macOS arm64 build**, use the repository's [macOS bug-report form](https://github.com/deepfilip/thought/issues/new?template=bug_report.yml). For source-build or reproduction problems, use the [build/reproduction form](https://github.com/deepfilip/thought/issues/new?template=build_reproduction.yml).

Before posting, remove sensitive information. **Never publish a seed phrase, private key, wallet password, wallet file, authentication token, or other secret.** For security-sensitive vulnerabilities, follow [`SECURITY.md`](SECURITY.md) instead of posting exploit details publicly.

Issues that are not specific to this community macOS release may belong with the [upstream Thought repository](https://github.com/thoughtnetwork/thought).

## Release source identity

R3 is tied to the qualified source state below:

- Release identity: `v0.18.4-community-r3`
- Qualified release commit: `a80c089edf82f4ccd76af2102e0af9d0daa7a261`
- Qualified release tree: `0d9c8ee25b8625af6c59b9558e083b86380ab72d`
- Qualified signed application executable SHA-256: `981ffc32676b919be4d81ea1744c477e26740426c33ad28de660bc3d161a972e`

The R3 release tag identifies the exact qualified commit above. Documentation-only commits may exist later on `master`; they do not change the source identity of the tagged R3 application.

The source-compliance companion published with the release contains the frozen Thought source, dependency-source custody, preserved relink material, component/source inventory, checksums, notices, and documented scope limitations.

## Building from source

Start with [`INSTALL.md`](INSTALL.md). For the community fork's Apple Silicon-specific source identity, limitations, environment capture, build-path and comparison guidance, see [`doc/macos-arm64-build.md`](doc/macos-arm64-build.md).

The build system and historical dependency stack are inherited from the upstream Thought Core codebase. The generic depends documentation does not by itself establish a validated native macOS arm64 recipe, and the published R3 release does not claim full historical build reproducibility. Always record the exact source revision and build environment when reporting results.

## Development and contributions

Development should be performed on separate branches and reviewed before integration. See [`CONTRIBUTING.md`](CONTRIBUTING.md) for the inherited contributor workflow and [`doc/developer-notes.md`](doc/developer-notes.md) for development guidance.

For release verification, prefer immutable commit/tag identities and published SHA-256 checksums over branch names.

## Upstream

This repository is a fork of the original Thought Core repository:

- Upstream source: [`thoughtnetwork/thought`](https://github.com/thoughtnetwork/thought)
- Project website: [thought.live](https://thought.live)

Community packaging and release statements in this repository should not be interpreted as Apple endorsement, Apple notarization, or an upstream Thought Network release unless explicitly stated.

## License

Thought Core is released under the terms of the MIT License. See [`COPYING`](COPYING) for the license text.

This is experimental financial software. Review the source, verify release checksums, and use appropriate caution with private keys and funds.
