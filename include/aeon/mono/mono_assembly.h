/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#pragma once

namespace aeon
{
namespace mono
{

class mono_class;
class mono_object;

class mono_assembly
{
public:
    explicit mono_assembly(MonoDomain *domain, const std::string &path);
    ~mono_assembly();

    int execute();
    int execute(int argc, char *argv[]);

    mono_class get_class(const std::string &name);
    mono_object new_object(const mono_class &cls);

private:
    MonoDomain *domain_;
    std::string path_;
    MonoAssembly *assembly_;
    MonoImage *image_;
};

} // namespace mono
} // namespace aeon
