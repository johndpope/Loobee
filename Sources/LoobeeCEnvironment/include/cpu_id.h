// This file is part of the Loobee package.
//
// (c) Andrey Savitsky <contact@qroc.pro>
//
// For the full copyright and license information, please view the LICENSE
// file that was distributed with this source code.

#include <stdint.h>
#include <stdbool.h>

typedef struct loobee_cpu_id {
    uint32_t f1c;
    uint32_t f1d;
} loobee_cpu_id_t __attribute((swift_name("CpuId")));

static __inline__ __attribute__((__always_inline__))
__attribute((swift_name("CpuId.current()")))
loobee_cpu_id_t loobee_cpu_id_current(void) {
    loobee_cpu_id_t cpu_id = {0, 0};

#if defined(__x86_64__) || defined(__i386__)
    uint32_t n;

    __asm__("cpuid" : "=a" (n) : "a" (0) : "ebx", "edx", "ecx");

    if (n >= 1) {
        __asm__("cpuid" : "=c" (cpu_id.f1c), "=d" (cpu_id.f1d) : "a" (1) : "ebx");
    }
#else
#   error Is not supported.
#endif
    return cpu_id;
}

#define LOOBEE_CPU_ID_HAS_FN(name, reg, bit) \
    static __inline__ __attribute__((__always_inline__)) \
    __attribute((swift_name("CpuId.has"#name"(self:)"))) \
    bool loobee_cpu_id_##name(const loobee_cpu_id_t *_Nonnull self) { \
        return ((self->reg) & (1U << bit)) != 0; \
    }

#define LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(name, bit) LOOBEE_CPU_ID_HAS_FN(name, f1c, bit)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Sse3, 0)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Pclmuldq, 1)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Dtes64, 2)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Monitor, 3)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Dscpl, 4)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Vmx, 5)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Smx, 6)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Eist, 7)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Tm2, 8)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Ssse3, 9)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Cnxtid, 10)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Fma, 12)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Cx16, 13)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Xtpr, 14)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Pdcm, 15)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Pcid, 17)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Dca, 18)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Sse41, 19)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Sse42, 20)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(X2apic, 21)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Movbe, 22)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Popcnt, 23)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Tscdeadline, 24)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Aes, 25)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Xsave, 26)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Osxsave, 27)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Avx, 28)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(F16c, 29)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Rdrand, 30)
#undef LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP

#define LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(name, bit) LOOBEE_CPU_ID_HAS_FN(name, f1d, bit)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Fpu, 0)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Vme, 1)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(De, 2)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Pse, 3)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Tsc, 4)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Msr, 5)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Pae, 6)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Mce, 7)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Cx8, 8)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Apic, 9)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Sep, 11)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Mtrr, 12)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Pge, 13)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Mca, 14)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Cmov, 15)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Pat, 16)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Pse36, 17)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Psn, 18)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Clfsh, 19)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Ds, 21)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Acpi, 22)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Mmx, 23)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Fxsr, 24)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Sse, 25)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Sse2, 26)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Ss, 27)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Htt, 28)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Tm, 29)

LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP(Pbe, 31)

#undef LOOBEE_CPU_ID_HAS_FN_REGISTER_GROUP

#undef LOOBEE_CPU_ID_HAS_FN