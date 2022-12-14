/*
 * Copyright (C) 2017-2021 Łukasz Kurowski <crackcomm@gmail.com>
 * Copyright (C) 2015 Ondrej Mosnacek <omosnacek@gmail.com>
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation: either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ARGON2_CUDA_PROGRAMCONTEXT_H
#define ARGON2_CUDA_PROGRAMCONTEXT_H

#include "crypto/argon2gpu/common.h"
#include "crypto/argon2gpu/cuda/global-context.h"

namespace argon2gpu
{
namespace cuda
{

class ProgramContext
{
private:
    const GlobalContext* globalContext;

    Type type;
    Version version;

public:
    const GlobalContext* getGlobalContext() const { return globalContext; }

    Type getArgon2Type() const { return type; }
    Version getArgon2Version() const { return version; }

    ProgramContext(
        const GlobalContext* globalContext,
        const std::vector<Device>& devices,
        Type type,
        Version version);
};

} // namespace cuda
} // namespace argon2gpu

#endif // ARGON2_CUDA_PROGRAMCONTEXT_H
