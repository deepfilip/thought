# Thought Wallet / Thought Core 0.18.4

This repository is a community-maintained fork of [`thoughtnetwork/thought`](https://github.com/thoughtnetwork/thought) used to maintain and publish a macOS Apple Silicon (arm64) community build of Thought Wallet / Thought Core 0.18.4.

Thought is an experimental peer-to-peer digital currency. The upstream project website is [thought.live](https://thought.live).

## Community macOS release

The current qualified community release line is:

**Thought Wallet 0.18.4 — macOS arm64 Community Build R2**

Release downloads are provided on this repository's [Releases page](https://github.com/deepfilip/thought/releases).

Expected public release files:

| File | SHA-256 |
| --- | --- |
| `Thought-Wallet-0.18.4-macOS-arm64-community-adhoc-r2.dmg` | `2780f3c737907cfc9b71574a6d3e59f3b40050cd172ef45d5ba4da4e6558982c` |
| `Thought-Wallet-0.18.4-macOS-arm64-community-source-compliance-r2.tar.gz` | `a4bc31fbdb5726497af4a640fc1eeec5376a03166789c2da2e45eeee3ef01363` |
| `SHA256SUMS.txt` | checksum list for the two files above |

Verify the downloaded DMG's SHA-256 before opening it.

## macOS security notice

The macOS community build is **ad-hoc signed and not Apple-notarized**. It is not signed with an Apple Developer ID certificate.

Because of that distribution model, macOS may block the first launch and report that Apple cannot check the application for malicious software. After verifying the download and only if you trust it, macOS provides an **Open Anyway** control under **System Settings → Privacy & Security** following an initial blocked launch attempt.

Do **not** disable Gatekeeper globally.

## First launch

Initial wallet setup can take tens of seconds while local wallet data is initialized. Subsequent launches should be substantially faster.

## Release source identity

The R2 application and source-compliance package are tied to the qualified source state below:

- Qualified release commit: `37e145b72de59db8f60c137a283a2c54b4e16c28`
- Qualified release tree: `5abba2a31eb0fc5dd0107aa9dc01d7e74a6a4132`
- Qualified application executable SHA-256: `5d66f7493518e09d097356fc2f0f5311ecb45861ae06eebce7188635dd127c90`

The community R2 release tag is intended to identify that exact qualified commit. Documentation-only commits may exist later on `master`; they do not change the source identity of the tagged R2 application.

The source-compliance companion published with the release contains the frozen Thought source, dependency-source custody, preserved relink material, component/source inventory, checksums, notices, and documented scope limitations.

## Building from source

See [`INSTALL.md`](INSTALL.md) and the platform-specific files under [`doc/`](doc/) for source-build guidance.

The build system and historical dependency stack are inherited from the upstream Thought Core codebase. Platform-specific work in this fork should be reviewed against the exact source revision being built.

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
