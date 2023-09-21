// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/hexdump.h>
#include <aeon/common/literals.h>
#include <cstdint>
#include <cctype>

namespace aeon::Common::HexDump
{

void PrettyPrint(FILE *dest, const void *src, const std::size_t len) noexcept
{
    fputs("--------|------------------------------------------------|----------------|\n", dest);
    fputs(" offset |00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F |0123456789ABCDEF|\n", dest);
    fputs("--------|------------------------------------------------|----------------|\n", dest);

    auto i = 0_size_t;
    auto c = 0_size_t;
    const auto *data = static_cast<const unsigned char *>(src);

    for (; i < len;)
    {
        const auto start = i;
        fprintf(dest, "%08X|", static_cast<unsigned int>(i));
        for (c = 0; c < 16 && i < len;) // write 16 bytes per line
        {
            fprintf(dest, "%02X ", static_cast<int>(data[i]));
            ++i;
            ++c;
        }

        const auto written = c;
        for (; c < 16; ++c) // finish off any incomplete bytes
            fputs("   ", dest);

        // write the text part
        fputc('|', dest);
        for (c = 0; c < written; ++c)
        {
            const auto byte = data[start + c];
            if (isprint(static_cast<int>(byte)))
                fputc(static_cast<char>(byte), dest);
            else
                fputc('.', dest);
        }

        for (; c < 16; ++c)
            fputc(' ', dest);

        fputs("|\n", dest);
    }

    fputs("---------------------------------------------------------------------------\n", dest);
}

void CppArray(FILE *dest, const char *const arrayName, const void *src, const std::size_t len) noexcept
{
    fprintf(dest, "std::array<char, %lu> %s = {\n", static_cast<unsigned long>(len), arrayName);

    const auto *data = static_cast<const unsigned char *>(src);

    auto bytesPerLine = 0ull;

    fputs("    ", dest);

    for (auto i = 0ull; i < len; ++i)
    {
        fprintf(dest, "0x%02X, ", static_cast<int>(data[i]));

        ++bytesPerLine;

        if (bytesPerLine >= 16)
        {
            fputs("\n    ", dest);
            bytesPerLine = 0;
        }
    }

    fputs("\n};\n", dest);
}

} // namespace aeon::Common::hexdump
