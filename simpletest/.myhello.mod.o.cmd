cmd_/home/wangml71/mydrivercode/simpletest/myhello.mod.o := arm-linux-gnueabi-gcc -Wp,-MMD,/home/wangml71/mydrivercode/simpletest/.myhello.mod.o.d -nostdinc -isystem /usr/lib/gcc-cross/arm-linux-gnueabi/11/include -I/home/wangml71/kernels/linux-5.10.186/arch/arm/include -I./arch/arm/include/generated -I/home/wangml71/kernels/linux-5.10.186/include -I./include -I/home/wangml71/kernels/linux-5.10.186/arch/arm/include/uapi -I./arch/arm/include/generated/uapi -I/home/wangml71/kernels/linux-5.10.186/include/uapi -I./include/generated/uapi -include /home/wangml71/kernels/linux-5.10.186/include/linux/kconfig.h -include /home/wangml71/kernels/linux-5.10.186/include/linux/compiler_types.h -D__KERNEL__ -mlittle-endian -fmacro-prefix-map=/home/wangml71/kernels/linux-5.10.186/= -Wall -Wundef -Werror=strict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -fshort-wchar -fno-PIE -Werror=implicit-function-declaration -Werror=implicit-int -Werror=return-type -Wno-format-security -std=gnu89 -fno-dwarf2-cfi-asm -fno-ipa-sra -mabi=aapcs-linux -mfpu=vfp -funwind-tables -marm -Wa,-mno-warn-deprecated -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -fno-delete-null-pointer-checks -Wno-frame-address -Wno-format-truncation -Wno-format-overflow -Wno-address-of-packed-member -O2 -fno-allow-store-data-races -Wframe-larger-than=1024 -fstack-protector-strong -Wimplicit-fallthrough -Wno-unused-but-set-variable -Wno-unused-const-variable -fomit-frame-pointer -g -Wdeclaration-after-statement -Wvla -Wno-pointer-sign -Wno-stringop-truncation -Wno-zero-length-bounds -Wno-array-bounds -Wno-stringop-overflow -Wno-restrict -Wno-maybe-uninitialized -fno-strict-overflow -fno-stack-check -fconserve-stack -Werror=date-time -Werror=incompatible-pointer-types -Werror=designated-init -Wno-packed-not-aligned  -DMODULE  -DKBUILD_BASENAME='"myhello.mod"' -DKBUILD_MODNAME='"myhello"' -c -o /home/wangml71/mydrivercode/simpletest/myhello.mod.o /home/wangml71/mydrivercode/simpletest/myhello.mod.c

source_/home/wangml71/mydrivercode/simpletest/myhello.mod.o := /home/wangml71/mydrivercode/simpletest/myhello.mod.c

deps_/home/wangml71/mydrivercode/simpletest/myhello.mod.o := \
    $(wildcard include/config/module/unload.h) \
    $(wildcard include/config/retpoline.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/kconfig.h \
    $(wildcard include/config/cc/version/text.h) \
    $(wildcard include/config/cpu/big/endian.h) \
    $(wildcard include/config/booger.h) \
    $(wildcard include/config/foo.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/compiler_types.h \
    $(wildcard include/config/have/arch/compiler/h.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/cc/has/asm/inline.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/compiler_attributes.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/compiler-gcc.h \
    $(wildcard include/config/arm64.h) \
    $(wildcard include/config/arch/use/builtin/bswap.h) \
    $(wildcard include/config/kcov.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/module.h \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/sysfs.h) \
    $(wildcard include/config/modules/tree/lookup.h) \
    $(wildcard include/config/livepatch.h) \
    $(wildcard include/config/unused/symbols.h) \
    $(wildcard include/config/module/sig.h) \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/kallsyms.h) \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/tracepoints.h) \
    $(wildcard include/config/tree/srcu.h) \
    $(wildcard include/config/bpf/events.h) \
    $(wildcard include/config/jump/label.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/event/tracing.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
    $(wildcard include/config/kprobes.h) \
    $(wildcard include/config/have/static/call/inline.h) \
    $(wildcard include/config/constructors.h) \
    $(wildcard include/config/function/error/injection.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/types.h \
    $(wildcard include/config/have/uid16.h) \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /home/wangml71/kernels/linux-5.10.186/include/uapi/linux/types.h \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/uapi/asm/types.h \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/int-ll64.h \
  /home/wangml71/kernels/linux-5.10.186/include/uapi/asm-generic/int-ll64.h \
  arch/arm/include/generated/uapi/asm/bitsperlong.h \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/bitsperlong.h \
  /home/wangml71/kernels/linux-5.10.186/include/uapi/asm-generic/bitsperlong.h \
  /home/wangml71/kernels/linux-5.10.186/include/uapi/linux/posix_types.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/stddef.h \
  /home/wangml71/kernels/linux-5.10.186/include/uapi/linux/stddef.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/compiler_types.h \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/uapi/asm/posix_types.h \
  /home/wangml71/kernels/linux-5.10.186/include/uapi/asm-generic/posix_types.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
    $(wildcard include/config/page/poisoning/zero.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/const.h \
  /home/wangml71/kernels/linux-5.10.186/include/vdso/const.h \
  /home/wangml71/kernels/linux-5.10.186/include/uapi/linux/const.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/atomic/sleep.h) \
    $(wildcard include/config/preempt/rt.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/panic/timeout.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/limits.h \
  /home/wangml71/kernels/linux-5.10.186/include/uapi/linux/limits.h \
  /home/wangml71/kernels/linux-5.10.186/include/vdso/limits.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/linkage.h \
    $(wildcard include/config/arch/use/sym/annotations.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/stringify.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/export.h \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/module/rel/crcs.h) \
    $(wildcard include/config/have/arch/prel32/relocations.h) \
    $(wildcard include/config/trim/unused/ksyms.h) \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/linkage.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/compiler.h \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/stack/validation.h) \
  arch/arm/include/generated/asm/rwonce.h \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/rwonce.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/kasan-checks.h \
    $(wildcard include/config/kasan.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/kcsan-checks.h \
    $(wildcard include/config/kcsan.h) \
    $(wildcard include/config/kcsan/ignore/atomics.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/bitops.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/bits.h \
  /home/wangml71/kernels/linux-5.10.186/include/vdso/bits.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/build_bug.h \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/bitops.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/typecheck.h \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/irqflags.h \
    $(wildcard include/config/cpu/v7m.h) \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/ptrace.h \
    $(wildcard include/config/arm/thumb.h) \
    $(wildcard include/config/thumb2/kernel.h) \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/uapi/asm/ptrace.h \
    $(wildcard include/config/cpu/endian/be8.h) \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/hwcap.h \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/uapi/asm/hwcap.h \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/irqflags.h \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/percpu.h \
    $(wildcard include/config/cpu/v6.h) \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/percpu.h \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/have/setup/per/cpu/area.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/percpu-defs.h \
    $(wildcard include/config/debug/force/weak/per/cpu.h) \
    $(wildcard include/config/amd/mem/encrypt.h) \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/barrier.h \
    $(wildcard include/config/cpu/32v6k.h) \
    $(wildcard include/config/cpu/xsc3.h) \
    $(wildcard include/config/cpu/fa526.h) \
    $(wildcard include/config/arm/heavy/mb.h) \
    $(wildcard include/config/arm/dma/mem/bufferable.h) \
    $(wildcard include/config/cpu/spectre.h) \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/barrier.h \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/bitops/non-atomic.h \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/bitops/builtin-__fls.h \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/bitops/builtin-__ffs.h \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/bitops/builtin-fls.h \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/bitops/builtin-ffs.h \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/bitops/ffz.h \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/bitops/fls64.h \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/bitops/sched.h \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/bitops/hweight.h \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/bitops/arch_hweight.h \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/bitops/const_hweight.h \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/bitops/lock.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/atomic.h \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/atomic.h \
    $(wildcard include/config/generic/atomic64.h) \
    $(wildcard include/config/arm/lpae.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/prefetch.h \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/processor.h \
    $(wildcard include/config/have/hw/breakpoint.h) \
    $(wildcard include/config/binfmt/elf/fdpic.h) \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/hw_breakpoint.h \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/unified.h \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/vdso/processor.h \
    $(wildcard include/config/arm/errata/754327.h) \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/cache.h \
    $(wildcard include/config/arm/l1/cache/shift.h) \
    $(wildcard include/config/aeabi.h) \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/cmpxchg.h \
    $(wildcard include/config/cpu/sa1100.h) \
    $(wildcard include/config/cpu/sa110.h) \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/cmpxchg-local.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/atomic-fallback.h \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/atomic-long.h \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/bitops/find.h \
    $(wildcard include/config/generic/find/first/bit.h) \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/bitops/le.h \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/uapi/asm/byteorder.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/byteorder/little_endian.h \
  /home/wangml71/kernels/linux-5.10.186/include/uapi/linux/byteorder/little_endian.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/swab.h \
  /home/wangml71/kernels/linux-5.10.186/include/uapi/linux/swab.h \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/swab.h \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/uapi/asm/swab.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/byteorder/generic.h \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/bitops/ext2-atomic-setbit.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/kstrtox.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/minmax.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/printk.h \
    $(wildcard include/config/message/loglevel/default.h) \
    $(wildcard include/config/console/loglevel/default.h) \
    $(wildcard include/config/console/loglevel/quiet.h) \
    $(wildcard include/config/early/printk.h) \
    $(wildcard include/config/printk/nmi.h) \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
    $(wildcard include/config/dynamic/debug/core.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/init.h \
    $(wildcard include/config/strict/kernel/rwx.h) \
    $(wildcard include/config/strict/module/rwx.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/kern_levels.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  /home/wangml71/kernels/linux-5.10.186/include/uapi/linux/kernel.h \
  /home/wangml71/kernels/linux-5.10.186/include/uapi/linux/sysinfo.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/ratelimit_types.h \
  /home/wangml71/kernels/linux-5.10.186/include/uapi/linux/param.h \
  arch/arm/include/generated/uapi/asm/param.h \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/param.h \
    $(wildcard include/config/hz.h) \
  /home/wangml71/kernels/linux-5.10.186/include/uapi/asm-generic/param.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/spinlock_types.h \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/debug/lock/alloc.h) \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/spinlock_types.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/lockdep_types.h \
    $(wildcard include/config/prove/raw/lock/nesting.h) \
    $(wildcard include/config/preempt/lock.h) \
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/lock/stat.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/rwlock_types.h \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/div64.h \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/compiler.h \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/div64.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/stat.h \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/uapi/asm/stat.h \
  /home/wangml71/kernels/linux-5.10.186/include/uapi/linux/stat.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
    $(wildcard include/config/posix/timers.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/math64.h \
    $(wildcard include/config/arch/supports/int128.h) \
  /home/wangml71/kernels/linux-5.10.186/include/vdso/math64.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/time64.h \
  /home/wangml71/kernels/linux-5.10.186/include/vdso/time64.h \
  /home/wangml71/kernels/linux-5.10.186/include/uapi/linux/time.h \
  /home/wangml71/kernels/linux-5.10.186/include/uapi/linux/time_types.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/time32.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/timex.h \
  /home/wangml71/kernels/linux-5.10.186/include/uapi/linux/timex.h \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/timex.h \
  /home/wangml71/kernels/linux-5.10.186/include/vdso/time32.h \
  /home/wangml71/kernels/linux-5.10.186/include/vdso/time.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/uidgid.h \
    $(wildcard include/config/multiuser.h) \
    $(wildcard include/config/user/ns.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/highuid.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/kmod.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/umh.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/gfp.h \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/zone/dma32.h) \
    $(wildcard include/config/zone/device.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/pm/sleep.h) \
    $(wildcard include/config/contig/alloc.h) \
    $(wildcard include/config/cma.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/mmdebug.h \
    $(wildcard include/config/debug/vm.h) \
    $(wildcard include/config/debug/virtual.h) \
    $(wildcard include/config/debug/vm/pgflags.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/bug.h \
    $(wildcard include/config/bug/on/data/corruption.h) \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/bug.h \
    $(wildcard include/config/debug/bugverbose.h) \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/opcodes.h \
    $(wildcard include/config/cpu/endian/be32.h) \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/instrumentation.h \
    $(wildcard include/config/debug/entry.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/memory/isolation.h) \
    $(wildcard include/config/zsmalloc.h) \
    $(wildcard include/config/shadow/call/stack.h) \
    $(wildcard include/config/memcg.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/sparsemem.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/compaction.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/transparent/hugepage.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/page/extension.h) \
    $(wildcard include/config/deferred/struct/page/init.h) \
    $(wildcard include/config/have/memoryless/nodes.h) \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/sparsemem/vmemmap.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
    $(wildcard include/config/memory/hotremove.h) \
    $(wildcard include/config/have/arch/pfn/valid.h) \
    $(wildcard include/config/holes/in/zone.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/spinlock.h \
    $(wildcard include/config/preemption.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/preempt.h \
    $(wildcard include/config/preempt/count.h) \
    $(wildcard include/config/trace/preempt/toggle.h) \
    $(wildcard include/config/preempt/notifiers.h) \
  arch/arm/include/generated/asm/preempt.h \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/preempt.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/thread_info.h \
    $(wildcard include/config/thread/info/in/task.h) \
    $(wildcard include/config/have/arch/within/stack/frames.h) \
    $(wildcard include/config/hardened/usercopy.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/restart_block.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/errno.h \
  /home/wangml71/kernels/linux-5.10.186/include/uapi/linux/errno.h \
  arch/arm/include/generated/uapi/asm/errno.h \
  /home/wangml71/kernels/linux-5.10.186/include/uapi/asm-generic/errno.h \
  /home/wangml71/kernels/linux-5.10.186/include/uapi/asm-generic/errno-base.h \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/thread_info.h \
    $(wildcard include/config/stackprotector/per/task.h) \
    $(wildcard include/config/crunch.h) \
    $(wildcard include/config/arm/thumbee.h) \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/fpstate.h \
    $(wildcard include/config/vfpv3.h) \
    $(wildcard include/config/iwmmxt.h) \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/page.h \
    $(wildcard include/config/cpu/copy/v4wt.h) \
    $(wildcard include/config/cpu/copy/v4wb.h) \
    $(wildcard include/config/cpu/copy/feroceon.h) \
    $(wildcard include/config/cpu/copy/fa.h) \
    $(wildcard include/config/cpu/xscale.h) \
    $(wildcard include/config/cpu/copy/v6.h) \
    $(wildcard include/config/kuser/helpers.h) \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/glue.h \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/pgtable-2level-types.h \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/memory.h \
    $(wildcard include/config/need/mach/memory/h.h) \
    $(wildcard include/config/page/offset.h) \
    $(wildcard include/config/dram/base.h) \
    $(wildcard include/config/dram/size.h) \
    $(wildcard include/config/xip/kernel.h) \
    $(wildcard include/config/have/tcm.h) \
    $(wildcard include/config/arm/patch/phys/virt.h) \
    $(wildcard include/config/phys/offset.h) \
    $(wildcard include/config/xip/phys/addr.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/sizes.h \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/memory_model.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/pfn.h \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/getorder.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/bottom_half.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/lockdep.h \
    $(wildcard include/config/debug/locking/api/selftests.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/smp.h \
    $(wildcard include/config/up/late/init.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/cpumask.h \
    $(wildcard include/config/cpumask/offstack.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/debug/per/cpu/maps.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/bitmap.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
    $(wildcard include/config/fortify/source.h) \
  /home/wangml71/kernels/linux-5.10.186/include/uapi/linux/string.h \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/string.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/smp_types.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/llist.h \
    $(wildcard include/config/arch/have/nmi/safe/cmpxchg.h) \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/smp.h \
  arch/arm/include/generated/asm/mmiowb.h \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/mmiowb.h \
    $(wildcard include/config/mmiowb.h) \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/spinlock.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/rwlock.h \
    $(wildcard include/config/preempt.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/spinlock_api_smp.h \
    $(wildcard include/config/inline/spin/lock.h) \
    $(wildcard include/config/inline/spin/lock/bh.h) \
    $(wildcard include/config/inline/spin/lock/irq.h) \
    $(wildcard include/config/inline/spin/lock/irqsave.h) \
    $(wildcard include/config/inline/spin/trylock.h) \
    $(wildcard include/config/inline/spin/trylock/bh.h) \
    $(wildcard include/config/uninline/spin/unlock.h) \
    $(wildcard include/config/inline/spin/unlock/bh.h) \
    $(wildcard include/config/inline/spin/unlock/irq.h) \
    $(wildcard include/config/inline/spin/unlock/irqrestore.h) \
    $(wildcard include/config/generic/lockbreak.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/rwlock_api_smp.h \
    $(wildcard include/config/inline/read/lock.h) \
    $(wildcard include/config/inline/write/lock.h) \
    $(wildcard include/config/inline/read/lock/bh.h) \
    $(wildcard include/config/inline/write/lock/bh.h) \
    $(wildcard include/config/inline/read/lock/irq.h) \
    $(wildcard include/config/inline/write/lock/irq.h) \
    $(wildcard include/config/inline/read/lock/irqsave.h) \
    $(wildcard include/config/inline/write/lock/irqsave.h) \
    $(wildcard include/config/inline/read/trylock.h) \
    $(wildcard include/config/inline/write/trylock.h) \
    $(wildcard include/config/inline/read/unlock.h) \
    $(wildcard include/config/inline/write/unlock.h) \
    $(wildcard include/config/inline/read/unlock/bh.h) \
    $(wildcard include/config/inline/write/unlock/bh.h) \
    $(wildcard include/config/inline/read/unlock/irq.h) \
    $(wildcard include/config/inline/write/unlock/irq.h) \
    $(wildcard include/config/inline/read/unlock/irqrestore.h) \
    $(wildcard include/config/inline/write/unlock/irqrestore.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/wait.h \
  arch/arm/include/generated/asm/current.h \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/current.h \
  /home/wangml71/kernels/linux-5.10.186/include/uapi/linux/wait.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
    $(wildcard include/config/numa/keep/meminfo.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/seqlock.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/mutex.h \
    $(wildcard include/config/mutex/spin/on/owner.h) \
    $(wildcard include/config/debug/mutexes.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/osq_lock.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/debug_locks.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/ww_mutex.h \
    $(wildcard include/config/debug/ww/mutex/slowpath.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/nodemask.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/pageblock-flags.h \
    $(wildcard include/config/hugetlb/page.h) \
    $(wildcard include/config/hugetlb/page/size/variable.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/page-flags-layout.h \
    $(wildcard include/config/numa/balancing.h) \
    $(wildcard include/config/kasan/sw/tags.h) \
  include/generated/bounds.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/mm_types.h \
    $(wildcard include/config/have/aligned/struct/page.h) \
    $(wildcard include/config/userfaultfd.h) \
    $(wildcard include/config/swap.h) \
    $(wildcard include/config/have/arch/compat/mmap/bases.h) \
    $(wildcard include/config/membarrier.h) \
    $(wildcard include/config/aio.h) \
    $(wildcard include/config/mmu/notifier.h) \
    $(wildcard include/config/arch/want/batched/unmap/tlb/flush.h) \
    $(wildcard include/config/iommu/support.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/mm_types_task.h \
    $(wildcard include/config/split/ptlock/cpus.h) \
    $(wildcard include/config/arch/enable/split/pmd/ptlock.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/auxvec.h \
  /home/wangml71/kernels/linux-5.10.186/include/uapi/linux/auxvec.h \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/auxvec.h \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/uapi/asm/auxvec.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/rbtree.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/rcupdate.h \
    $(wildcard include/config/preempt/rcu.h) \
    $(wildcard include/config/tiny/rcu.h) \
    $(wildcard include/config/tasks/rcu/generic.h) \
    $(wildcard include/config/rcu/stall/common.h) \
    $(wildcard include/config/no/hz/full.h) \
    $(wildcard include/config/rcu/nocb/cpu.h) \
    $(wildcard include/config/tasks/rcu.h) \
    $(wildcard include/config/tasks/trace/rcu.h) \
    $(wildcard include/config/tasks/rude/rcu.h) \
    $(wildcard include/config/tree/rcu.h) \
    $(wildcard include/config/debug/objects/rcu/head.h) \
    $(wildcard include/config/prove/rcu.h) \
    $(wildcard include/config/rcu/boost.h) \
    $(wildcard include/config/arch/weak/release/acquire.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/rcutree.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/rwsem.h \
    $(wildcard include/config/rwsem/spin/on/owner.h) \
    $(wildcard include/config/debug/rwsems.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/err.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/completion.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/swait.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/uprobes.h \
    $(wildcard include/config/uprobes.h) \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/uprobes.h \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/probes.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/workqueue.h \
    $(wildcard include/config/debug/objects/work.h) \
    $(wildcard include/config/freezer.h) \
    $(wildcard include/config/wq/watchdog.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/timer.h \
    $(wildcard include/config/debug/objects/timers.h) \
    $(wildcard include/config/no/hz/common.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/ktime.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/jiffies.h \
  /home/wangml71/kernels/linux-5.10.186/include/vdso/jiffies.h \
  include/generated/timeconst.h \
  /home/wangml71/kernels/linux-5.10.186/include/vdso/ktime.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/timekeeping.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/timekeeping32.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/debugobjects.h \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/debug/objects/free.h) \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/mmu.h \
    $(wildcard include/config/cpu/has/asid.h) \
    $(wildcard include/config/vdso.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/page-flags.h \
    $(wildcard include/config/arch/uses/pg/uncached.h) \
    $(wildcard include/config/memory/failure.h) \
    $(wildcard include/config/idle/page/tracking.h) \
    $(wildcard include/config/thp/swap.h) \
    $(wildcard include/config/ksm.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/memory_hotplug.h \
    $(wildcard include/config/arch/has/add/pages.h) \
    $(wildcard include/config/have/arch/nodedata/extension.h) \
    $(wildcard include/config/have/bootmem/info/node.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/notifier.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/srcu.h \
    $(wildcard include/config/tiny/srcu.h) \
    $(wildcard include/config/srcu.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/rcu_segcblist.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/srcutree.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/rcu_node_tree.h \
    $(wildcard include/config/rcu/fanout.h) \
    $(wildcard include/config/rcu/fanout/leaf.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/topology.h \
    $(wildcard include/config/use/percpu/numa/node/id.h) \
    $(wildcard include/config/sched/smt.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/arch_topology.h \
    $(wildcard include/config/generic/arch/topology.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/percpu.h \
    $(wildcard include/config/need/per/cpu/embed/first/chunk.h) \
    $(wildcard include/config/need/per/cpu/page/first/chunk.h) \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/topology.h \
    $(wildcard include/config/arm/cpu/topology.h) \
    $(wildcard include/config/bl/switcher.h) \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/topology.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/sysctl.h \
    $(wildcard include/config/sysctl.h) \
  /home/wangml71/kernels/linux-5.10.186/include/uapi/linux/sysctl.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/elf.h \
    $(wildcard include/config/arch/use/gnu/property.h) \
    $(wildcard include/config/arch/have/elf/prot.h) \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/elf.h \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/vdso_datapage.h \
  /home/wangml71/kernels/linux-5.10.186/include/vdso/datapage.h \
    $(wildcard include/config/arch/has/vdso/data.h) \
  /home/wangml71/kernels/linux-5.10.186/include/uapi/asm-generic/errno-base.h \
  /home/wangml71/kernels/linux-5.10.186/include/vdso/clocksource.h \
    $(wildcard include/config/generic/gettimeofday.h) \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/vdso/clocksource.h \
  /home/wangml71/kernels/linux-5.10.186/include/vdso/processor.h \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/vdso/gettimeofday.h \
    $(wildcard include/config/arm/arch/timer.h) \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/unistd.h \
    $(wildcard include/config/oabi/compat.h) \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/uapi/asm/unistd.h \
  arch/arm/include/generated/uapi/asm/unistd-eabi.h \
  arch/arm/include/generated/uapi/asm/unistd-common.h \
  arch/arm/include/generated/asm/unistd-nr.h \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/vdso/cp15.h \
    $(wildcard include/config/cpu/cp15.h) \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/user.h \
  /home/wangml71/kernels/linux-5.10.186/include/uapi/linux/elf.h \
  /home/wangml71/kernels/linux-5.10.186/include/uapi/linux/elf-em.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/kobject.h \
    $(wildcard include/config/uevent/helper.h) \
    $(wildcard include/config/debug/kobject/release.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/sysfs.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/kernfs.h \
    $(wildcard include/config/kernfs.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/idr.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/radix-tree.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/xarray.h \
    $(wildcard include/config/xarray/multi.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/kconfig.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/local_lock.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/local_lock_internal.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/kobject_ns.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/kref.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/refcount.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/moduleparam.h \
    $(wildcard include/config/alpha.h) \
    $(wildcard include/config/ia64.h) \
    $(wildcard include/config/ppc64.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/jump_label.h \
    $(wildcard include/config/have/arch/jump/label/relative.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/rbtree_latch.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/error-injection.h \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/error-injection.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/tracepoint-defs.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/static_key.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/static_call_types.h \
    $(wildcard include/config/have/static/call.h) \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/module.h \
    $(wildcard include/config/arm/unwind.h) \
    $(wildcard include/config/arm/module/plts.h) \
  /home/wangml71/kernels/linux-5.10.186/include/asm-generic/module.h \
    $(wildcard include/config/have/mod/arch/specific.h) \
    $(wildcard include/config/modules/use/elf/rel.h) \
    $(wildcard include/config/modules/use/elf/rela.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/build-salt.h \
    $(wildcard include/config/build/salt.h) \
  /home/wangml71/kernels/linux-5.10.186/include/linux/elfnote.h \
  /home/wangml71/kernels/linux-5.10.186/include/linux/vermagic.h \
  include/generated/utsrelease.h \
  /home/wangml71/kernels/linux-5.10.186/arch/arm/include/asm/vermagic.h \

/home/wangml71/mydrivercode/simpletest/myhello.mod.o: $(deps_/home/wangml71/mydrivercode/simpletest/myhello.mod.o)

$(deps_/home/wangml71/mydrivercode/simpletest/myhello.mod.o):
