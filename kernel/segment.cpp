#include "segment.hpp"

#include "asmfunc.h"

namespace {
std::array<SegmentDescriptor, 3> gdt;
}

void SetCodeSegment(SegmentDescriptor& desc, DescriptorType type,
                    unsigned int descriptor_privilege_level) {
    desc.data = 0;

    // NOTE: 64bitモードであればbaseとlimit,granularityは設定不要

    desc.bits.type = type;
    // NOTE: コードセグメント、データセグメントであれば1を設定する
    desc.bits.system_segment = 1;
    desc.bits.descriptor_privilege_level = descriptor_privilege_level;
    desc.bits.present = 1;
    desc.bits.available = 0;
    desc.bits.long_mode = 1;
    // NOTE: 64bitモードでコードセグメントであれば必ず0とする
    desc.bits.default_operation_size = 0;
}

void SetDataSegment(SegmentDescriptor& desc, DescriptorType type,
                    unsigned int descriptor_privilege_level) {
    desc.data = 0;

    // NOTE: 64bitモードであればbaseとlimit,granularityは設定不要

    desc.bits.type = type;
    // NOTE: コードセグメント、データセグメントであれば1を設定する
    desc.bits.system_segment = 1;
    desc.bits.descriptor_privilege_level = descriptor_privilege_level;
    desc.bits.present = 1;
    desc.bits.available = 0;
    // NOTE: データセグメントでは予約語なので必ず0を設定する
    desc.bits.long_mode = 0;
    // NOTE: syscall命令と整合性を取るため1を設定する
    desc.bits.default_operation_size = 1;
}

void SetupSegments() {
    gdt[0].data = 0;
    SetCodeSegment(gdt[1], DescriptorType::kExecuteRead, 0);
    SetDataSegment(gdt[2], DescriptorType::kReadWrite, 0);
    LoadGDT(sizeof(gdt) - 1, reinterpret_cast<uintptr_t>(&gdt[0]));
}