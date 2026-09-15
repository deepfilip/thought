# macOS Apple Silicon build and reproduction guide

This guide is the fork-specific entry point for building or attempting to reproduce Thought Wallet / Thought Core 0.18.4 on macOS Apple Silicon.

It is deliberately conservative: it separates **verified R3 release identity** from **environment-dependent source-build steps** and does not claim that the repository currently provides a one-command, byte-for-byte reproducible native arm64 build.

## 1. What is verified for Community Build R3

The published release is:

- tag: `v0.18.4-community-r3`
- qualified repository commit: `a80c089edf82f4ccd76af2102e0af9d0daa7a261`
- qualified repository tree: `0d9c8ee25b8625af6c59b9558e083b86380ab72d`
- qualified signed application executable SHA-256: `981ffc32676b919be4d81ea1744c477e26740426c33ad28de660bc3d161a972e`
- DMG: `Thought-Wallet-0.18.4-macOS-arm64-community-adhoc-r3.dmg`
- DMG SHA-256: `656a8b69dc7bff05b6d93e799fc4daf49b2f74f7123a8ca2a8e42c779e7d6f4d`

The release is **ad-hoc signed and not Apple-notarized**. Its release notes explicitly do **not** claim full historical build reproducibility.

If your goal is to compare with R3, start from the tag rather than `master`:

```bash
git fetch --tags
git checkout --detach v0.18.4-community-r3
git rev-parse HEAD
git rev-parse HEAD^{tree}
```

Expected R3 values:

```text
a80c089edf82f4ccd76af2102e0af9d0daa7a261
0d9c8ee25b8625af6c59b9558e083b86380ab72d
```

## 2. Record the build environment first

Before changing packages or starting a build, capture the environment that can affect the result:

```bash
uname -m
sw_vers
xcodebuild -version
clang --version
make --version
python3 --version
```

On Apple Silicon, `uname -m` should normally report `arm64`. If you are intentionally building under Rosetta or another translated/cross-compiled environment, record that explicitly.

Also record:

- the exact Git commit and tree;
- whether the shell is native arm64 or translated;
- Xcode / Command Line Tools version;
- Homebrew prefix and relevant package versions if Homebrew is used;
- the exact dependency source/cache used;
- every configure flag;
- the exact build command.

This information is more useful for reproduction than a branch name alone.

## 3. Understand the inherited build documentation

Thought Core's generic build path uses the repository's [`depends`](../depends/README.md) system and the flow described in [`build-generic.md`](build-generic.md).

The inherited depends documentation lists `x86_64-apple-darwin11` as a macOS host triplet. That is an **x86_64** target and must not be presented as a validated native Apple Silicon recipe.

The older [`build-osx.md`](build-osx.md) is preserved for historical context. It also contains x86_64-era assumptions. Use it as legacy reference, not as proof of the R3 build environment.

## 4. Dependency/build attempt

For a native-host attempt, the generic depends documentation permits building for the current host without explicitly supplying `HOST`:

```bash
cd depends
make -j4
```

This command is a **build attempt**, not a guarantee that every inherited dependency recipe will succeed on a particular current macOS/Xcode combination.

If the depends build succeeds, record the actual generated host prefix. Do not guess a prefix name or substitute the legacy x86_64 macOS triplet and then describe the result as a native arm64 build.

Return to the repository root and use the actual prefix produced by that dependency build:

```bash
cd ..
./autogen.sh
./configure --prefix="<actual depends prefix>"
make -j4
```

For additional configure options:

```bash
./configure --help
```

If the native depends route fails before producing a usable prefix, stop there and capture the first reproducible failure. Do not paper over the failure by silently mixing unrelated Homebrew/system libraries and then call the result a reproduction of R3.

## 5. Inspect a successful build

If the build completes, record the architecture and version identity of the artifacts you actually produced. Typical checks include:

```bash
file src/thoughtd
file src/qt/thought-qt
./src/thoughtd --version
./src/qt/thought-qt --version
shasum -a 256 src/thoughtd
shasum -a 256 src/qt/thought-qt
```

If a listed artifact was not built, report that fact rather than changing the claim.

A different SHA-256 from the qualified R3 executable does **not** by itself prove a defect: the published R3 release does not claim full historical build reproducibility, and compiler/SDK/dependency/packaging differences can change output bytes.

## 6. Packaging is a separate question

This guide does not claim that the legacy `make deploy` path reproduces the published R3 DMG, nor does it define Developer ID signing or notarization.

The published R3 package is ad-hoc signed and non-notarized. Do not describe a locally produced package as the R3 release unless it is the exact published release artifact with the published checksum.

## 7. Reporting a failed or partial reproduction

Use the repository's [build/reproduction issue form](../.github/ISSUE_TEMPLATE/build_reproduction.yml) and include:

- exact source tag/commit/tree;
- Apple chip and macOS version;
- native arm64 vs translated shell;
- Xcode / Command Line Tools and clang versions;
- dependency route and prefix;
- exact commands;
- the first deterministic failure;
- architecture/version/hash of any artifacts that were produced.

For ordinary application/runtime problems with the published community build, use the existing [macOS bug-report form](../.github/ISSUE_TEMPLATE/bug_report.yml).

Before posting logs, remove secrets and sensitive wallet information. **Never post seed phrases, private keys, wallet passwords, wallet files, authentication tokens or other secrets.**

Security-sensitive vulnerabilities should follow [`SECURITY.md`](../SECURITY.md) instead of being disclosed in a public build issue.

## Related documentation

- [`../INSTALL.md`](../INSTALL.md) — build documentation entry point
- [`build-generic.md`](build-generic.md) — inherited generic depends-based flow
- [`../depends/README.md`](../depends/README.md) — depends system reference
- [`build-osx.md`](build-osx.md) — inherited legacy macOS notes
- [`macos-fast-sync.md`](macos-fast-sync.md) — optional fast initial synchronization guide for users of the macOS wallet
