#pragma once

enum CPUDisAsmMode
{
	CPUDisAsm_DumpMode,
	CPUDisAsm_InterpreterMode,
	//CPUDisAsm_NormalMode,
	CPUDisAsm_CompilerElfMode,
};

class CPUDisAsm
{
protected:
	const CPUDisAsmMode m_mode;

	virtual void Write(const std::string& value)
	{
		switch(m_mode)
		{
			case CPUDisAsm_DumpMode:
				last_opcode = fmt::format("\t%08x:\t%02x %02x %02x %02x\t%s\n", dump_pc,
					offset[dump_pc],
					offset[dump_pc + 1],
					offset[dump_pc + 2],
					offset[dump_pc + 3], value);
			break;

			case CPUDisAsm_InterpreterMode:
				last_opcode = fmt::format("[%08x]  %02x %02x %02x %02x: %s", dump_pc,
					offset[dump_pc],
					offset[dump_pc + 1],
					offset[dump_pc + 2],
					offset[dump_pc + 3], value);
			break;

			case CPUDisAsm_CompilerElfMode:
				last_opcode = value + "\n";
			break;
		}
	}

public:
	std::string last_opcode;
	u32 dump_pc;
	u8* offset;

protected:
	CPUDisAsm(CPUDisAsmMode mode) 
		: m_mode(mode)
		, offset(0)
	{
	}

	virtual u32 DisAsmBranchTarget(const s32 imm) = 0;

	std::string FixOp(std::string op)
	{
		op.resize(std::max<std::size_t>(op.length(), 10), ' ');
		return op;
	}

public:
	virtual u32 disasm(u32 pc) = 0;
};
