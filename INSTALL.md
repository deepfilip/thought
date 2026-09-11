# Building Thought Core

This fork contains the community-maintained macOS Apple Silicon (arm64) release work for Thought Wallet / Thought Core 0.18.4, while much of the build system and build documentation is inherited from the upstream codebase.

## Choose the right guide

- **macOS Apple Silicon / arm64:** [`doc/macos-arm64-build.md`](doc/macos-arm64-build.md)
- **Generic depends-based build flow:** [`doc/build-generic.md`](doc/build-generic.md)
- **Depends system reference:** [`depends/README.md`](depends/README.md)
- **Legacy macOS notes:** [`doc/build-osx.md`](doc/build-osx.md)
- **Unix:** [`doc/build-unix.md`](doc/build-unix.md)
- **Windows:** [`doc/build-windows.md`](doc/build-windows.md)
- **Developer notes:** [`doc/developer-notes.md`](doc/developer-notes.md)

The legacy macOS guide is retained for historical context. It includes older Homebrew and x86_64-oriented instructions and should not be treated as the current Apple Silicon reproduction guide.

## Start from an immutable source identity

If you are comparing a source build with the published macOS arm64 Community Build R2, use the release tag rather than a moving branch:

```bash
git fetch --tags
git checkout --detach v0.18.4-community-r2
git rev-parse HEAD
git rev-parse HEAD^{tree}
```

For R2, the published source identity is:

- commit `37e145b72de59db8f60c137a283a2c54b4e16c28`
- tree `5abba2a31eb0fc5dd0107aa9dc01d7e74a6a4132`

Later documentation-only commits on `master` do not change the tagged R2 application source identity.

## Reproducibility boundary

The R2 release is an ad-hoc-signed, non-notarized community build and does **not** claim full historical build reproducibility. The release's source-compliance companion preserves source/dependency custody, relink material and documented limitations, but a fresh build on another machine may differ because of toolchain, SDK, dependency, environment or packaging differences.

Do not treat a different build hash by itself as proof of a defect or compromise.

## Generic build flow

The inherited build system uses the repository's `depends` prefix. The generic flow is:

```bash
cd depends
make -j4
cd ..
./autogen.sh
./configure --prefix="<actual depends prefix>"
make -j4
```

Read [`depends/README.md`](depends/README.md) and [`doc/build-generic.md`](doc/build-generic.md) before choosing a host/prefix.

For Apple Silicon specifically, do **not** assume that the legacy `x86_64-apple-darwin11` host triplet is a native arm64 recipe. The inherited depends documentation lists that triplet for macOS but does not document a validated arm64 macOS host triplet. The Apple Silicon guide explains how to record this boundary and report a failed or incomplete reproduction attempt without guessing.

## Reporting build or reproduction problems

Use the [build/reproduction issue form](https://github.com/deepfilip/thought/issues/new?template=build_reproduction.yml) and include the exact source ref, hardware/OS, Xcode/clang versions, dependency route, commands and resulting error or artifact identity.

Never post seed phrases, private keys, wallet passwords, wallet files, authentication tokens or other secrets. Security-sensitive vulnerabilities belong under [`SECURITY.md`](SECURITY.md), not in a public build issue.
