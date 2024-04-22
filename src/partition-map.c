/* -------------------------------------------

    Copyright Mahrouss Logic

------------------------------------------- */

#include <lib/partition-map.h>
#include <lib/string.h>

// include this for documentation.

static const __SIZE_TYPE__ mp_filesystems_count = 1;
static const caddr_t mp_filesystems[] = { "NewFS" };

/// @brief check if filesystem is supported by CoreBoot.
/// @param fs the filesystem magic, as provided by EPM.
boolean mp_filesystem_exists(caddr_t fs)
{
    if (fs == nil ||
        *fs == 0)
        return no;

    for (size_t fs_index = 0; fs_index < mp_filesystems_count; fs_index++)
    {
        if (strncmp(mp_filesystems[fs_index], fs, strlen(mp_filesystems[fs_index])) == 0)
        {
            return yes;
        }
    }

    return no;
}
