# Security Policy

## Scope

This repository maintains a **community macOS Apple Silicon (arm64) build** of Thought Wallet / Thought Core 0.18.4. It is not an official upstream Thought Network release.

The currently supported community release is:

- `v0.18.4-community-r2`

Security reports should identify the exact release/tag and macOS version involved whenever possible.

## Reporting a security issue

**Do not publish sensitive vulnerability details, exploit material, secrets, private keys, seed phrases, wallet passwords, wallet files, authentication tokens, or personally identifying wallet data in a public GitHub issue.**

For an ordinary reproducible macOS bug that does not expose sensitive information, use the repository's macOS bug-report form.

For a security-sensitive vulnerability:

1. Do not open a public issue containing exploit details or secrets.
2. If GitHub displays a private **Report a vulnerability** option under the repository's Security area, use that private channel.
3. If no private reporting channel is available, contact the maintainer through a private channel associated with the GitHub account before sharing sensitive technical details.
4. Until a private channel is established, disclose only the minimum non-sensitive information needed to indicate that a security report exists.

## Financial-software caution

Thought Wallet handles cryptographic keys and financial state. Before testing a suspected vulnerability:

- use disposable test data where possible;
- do not expose real seed phrases or private keys;
- do not send real funds merely to reproduce a defect;
- back up wallet data before experiments that could affect it;
- distinguish defects in this community macOS packaging/build from upstream protocol or application defects.

## Community / upstream boundary

Issues specific to the macOS arm64 community build, packaging, startup, or distribution belong here. Issues that reproduce independently of this community macOS release may belong with the upstream project at [`thoughtnetwork/thought`](https://github.com/thoughtnetwork/thought).

This policy does not imply Apple endorsement, Apple notarization, or upstream Thought Network endorsement of this community release.
