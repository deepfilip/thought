# Fast initial blockchain sync on macOS

This guide is for users of the **Thought Wallet 0.18.4 macOS Apple Silicon (arm64) Community Build R2** who want to avoid downloading the entire historical blockchain from peers from scratch.

Fast sync is **optional**. Thought Wallet can synchronize normally from the peer-to-peer network without using a snapshot.

## What the snapshot is

Phil Grim's Thought Quickstart Guide publishes a compressed Thought blockchain snapshot at:

- Quickstart / archive information: https://idea-01.insufficient-light.com/
- Direct Linux-format archive: https://idea-01.insufficient-light.com/data/thought-chain.tar.gz

The archive contains these blockchain database directories:

- `blocks/`
- `chainstate/`
- `evodb/`

The archive does **not** replace your `wallet.dat`.

The snapshot page says new archives are posted approximately monthly. **Check the date shown on the source page before downloading rather than assuming an old cached copy is current.** As of 10 September 2026, the page listed **06 June 2026** as the latest archive.

### macOS compatibility

Although the upstream Quickstart instructions are written for Linux, the blockchain database contents are not a Linux application binary. On **10 September 2026**, the 06 June 2026 snapshot was tested with Community Build R2 on macOS Apple Silicon: R2 opened the snapshot successfully and then caught up from the snapshot state to the live Thought network.

That test establishes compatibility with the snapshot tested on that date. It does not automatically authenticate or qualify future replacement archives.

## Trust and safety notes

The snapshot is **not hosted by this GitHub repository and is not part of the R2 release assets**. It is a maintainer-hosted convenience download linked from Phil's Thought Quickstart Guide.

At the time of the macOS compatibility test, the snapshot source page did not publish a cryptographic checksum for the archive. Because the snapshot contains prebuilt `chainstate` and `evodb` database state rather than only raw blocks, users should treat it as a convenience/trust trade-off rather than as equivalent to synchronizing everything from peers from scratch.

Before modifying an existing Thought data directory:

1. Quit Thought Wallet completely.
2. Make a separate backup of `wallet.dat`.
3. Never replace, delete, download, or share `wallet.dat` as part of the snapshot procedure.
4. Preserve the existing `blocks`, `chainstate`, and `evodb` directories until the replacement snapshot has started and synchronized successfully.
5. Never post wallet seeds, private keys, wallet passwords, or wallet files in an issue or support request.

If the wallet contains meaningful funds and you are unsure about any step, stop and ask for help before changing the data directory.

## 1. Install Community Build R2

Download the current macOS Apple Silicon DMG from the repository's [R2 release](https://github.com/deepfilip/thought/releases/tag/v0.18.4-community-r2).

Verify the DMG SHA-256 before opening it:

`2780f3c737907cfc9b71574a6d3e59f3b40050cd172ef45d5ba4da4e6558982c`

Open the DMG and drag `Thought-Qt.app` onto the **Applications** shortcut inside the DMG window. After the copy completes, launch the installed application from `/Applications`.

## 2. Identify the active Thought data directory

For a normal macOS installation, the default is:

`~/Library/Application Support/ThoughtCore`

Existing Thought users may have selected a **custom data directory** in an earlier version. Thought Wallet remembers that choice and can continue using it on later launches, so do not assume the default path if you have previously selected another location.

If you know you use the default path, continue below. If you previously chose a custom location, use that active directory instead.

### Read-only way to confirm a custom active directory

With Thought Wallet running, advanced users can inspect which blockchain database files the process actually has open:

```bash
PID=$(pgrep -x Thought-Qt | head -n 1)
lsof -p "$PID" 2>/dev/null | grep -E '/blocks/|/chainstate/|/evodb/' | head
```

The path before `/blocks`, `/chainstate`, or `/evodb` is the active Thought data directory.

Quit Thought Wallet again before changing any files.

## 3. Download and unpack the snapshot

Download `thought-chain.tar.gz` from the Quickstart page above. macOS can unpack the `.tar.gz` archive normally.

After extraction you should have exactly the snapshot database directories:

```text
blocks/
chainstate/
evodb/
```

Do not copy an unrelated `wallet.dat` into your Thought data directory.

## 4. Back up an existing wallet first

If your active Thought data directory already contains `wallet.dat`, copy it to a separate safe location before doing anything with the chain databases.

For an existing installation, also preserve the current `blocks`, `chainstate`, and `evodb` directories instead of deleting them immediately. Keeping the old chain state makes rollback straightforward if the snapshot fails to open.

## 5. Put only the blockchain snapshot into the active data directory

With Thought Wallet fully closed:

1. Move the existing `blocks`, `chainstate`, and `evodb` directories out of the active Thought data directory into a backup folder.
2. Copy the snapshot's `blocks`, `chainstate`, and `evodb` directories into the active Thought data directory.
3. Leave your existing `wallet.dat` and other wallet-specific files in place.

The final layout should include your existing wallet plus the replacement chain databases, for example:

```text
ThoughtCore/
├── wallet.dat        # your existing wallet — preserve this
├── blocks/           # from snapshot
├── chainstate/       # from snapshot
└── evodb/            # from snapshot
```

## 6. Start Thought Wallet and let it catch up

Launch `Thought-Qt.app` normally from Applications.

The wallet should open at approximately the snapshot's chain date rather than years in the past, connect to Thought peers, and download the remaining blocks from the live network. Catch-up time varies with snapshot age, network conditions, storage speed, and hardware.

Do not delete your wallet or old-chain backups until the wallet:

- opens without database errors;
- shows the expected wallet/balance;
- connects to peers; and
- reaches the current chain tip.

## Troubleshooting

### It still says years behind

The most common cause on an existing installation is that the snapshot was copied into the **default** macOS directory while Thought Wallet is actually using a remembered **custom** data directory. Re-check the active directory as described above.

### macOS says Terminal cannot read an external drive

If your custom data directory is on removable storage, macOS privacy controls may prevent Terminal from reading it. In **System Settings → Privacy & Security**, allow Terminal access to the relevant removable volume (or, if necessary, Full Disk Access), then quit and reopen Terminal.

### The snapshot will not open

Quit the wallet and restore the preserved old `blocks`, `chainstate`, and `evodb` directories. Your backed-up `wallet.dat` should remain untouched.

For reproducible problems specific to Community Build R2, use the repository's [macOS bug-report form](https://github.com/deepfilip/thought/issues/new?template=bug_report.yml). Never attach `wallet.dat` or disclose private keys, seeds, or wallet passwords.

## Why this is separate from the R2 release

Community Build R2 remains a normal Thought Wallet application release. The snapshot is an optional onboarding accelerator maintained outside this repository and can be updated independently of the application. Keeping the two separate avoids silently bundling mutable blockchain state into the signed/qualified application package.
