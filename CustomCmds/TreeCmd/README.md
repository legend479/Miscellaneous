# Bash Script: Directory Tree Viewer

This custom Bash script, named "Tree" is designed to display a hierarchical tree view of directories and files within a specified directory. It provides several options for customizing the output, including sorting, filtering, and limiting the depth of the tree.

## Usage:

```bash
./directory_tree_viewer.sh [OPTIONS] [DIRECTORY]
```

- `DIRECTORY`: The optional directory path to start the tree view (default is the current directory).

## Options:

- `-A`: Include hidden files and directories.
- `-D DEPTH`: Limit the depth of the tree to a specified integer depth level. Use a non-negative integer for DEPTH.
- `-a`: Sort entries in ascending order based on the ninth field (filename).
- `-d`: Sort entries in descending order based on the ninth field (filename).
- `-s`: Sort entries by size in ascending order.
- `-h`: Display help information.

## Features:

- Displays a tree structure of directories and files.
- Supports custom sorting options.
- Filters hidden files and directories by default.
- Allows you to limit the depth of the tree view.
- Provides options for sorting entries by name or size.
- Handles spaces and special characters in file and directory names.

## Examples:

1. Display the directory tree of the current directory with hidden files and directories:

   ```bash
   ./directory_tree_viewer.sh -A
   ```

2. Display the directory tree of a specific directory with a depth limit of 3:

   ```bash
   ./directory_tree_viewer.sh -D 3 /path/to/directory
   ```

3. Display the directory tree sorted by file size in ascending order:

   ```bash
   ./directory_tree_viewer.sh -s
   ```

4. Display the directory tree sorted by filename in descending order:

   ```bash
   ./directory_tree_viewer.sh -d
   ```

## Notes:

- This script is for viewing directory structures and does not modify any files or directories.
- Use the `-h` option to display help information and see available options.

Feel free to customize and extend this script to suit your needs.