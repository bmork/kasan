/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LINUX_KCOV_IOCTLS_H
#define _LINUX_KCOV_IOCTLS_H

#include <linux/types.h>

struct kcov_remote_arg {
	unsigned int	trace_mode;
	unsigned int	area_size;
	unsigned int	num_handles;
	__u64		common_handle;
	__u64		handles[0];
};

#define KCOV_REMOTE_MAX_HANDLES		0x10000

#define KCOV_INIT_TRACE			_IOR('c', 1, unsigned long)
#define KCOV_ENABLE			_IO('c', 100)
#define KCOV_DISABLE			_IO('c', 101)
#define KCOV_REMOTE_ENABLE		_IOW('c', 102, struct kcov_remote_arg)

enum {
	/*
	 * Tracing coverage collection mode.
	 * Covered PCs are collected in a per-task buffer.
	 * In new KCOV version the mode is chosen by calling
	 * ioctl(fd, KCOV_ENABLE, mode). In older versions the mode argument
	 * was supposed to be 0 in such a call. So, for reasons of backward
	 * compatibility, we have chosen the value KCOV_TRACE_PC to be 0.
	 */
	KCOV_TRACE_PC = 0,
	/* Collecting comparison operands mode. */
	KCOV_TRACE_CMP = 1,
};

/*
 * The format for the types of collected comparisons.
 *
 * Bit 0 shows whether one of the arguments is a compile-time constant.
 * Bits 1 & 2 contain log2 of the argument size, up to 8 bytes.
 */
#define KCOV_CMP_CONST          (1 << 0)
#define KCOV_CMP_SIZE(n)        ((n) << 1)
#define KCOV_CMP_MASK           KCOV_CMP_SIZE(3)

#define KCOV_REMOTE_HANDLE_USB  0x4242000000000000ull

static inline __u64 kcov_remote_handle_usb(unsigned int bus)
{
	return KCOV_REMOTE_HANDLE_USB + (__u64)bus;
}

#endif /* _LINUX_KCOV_IOCTLS_H */
