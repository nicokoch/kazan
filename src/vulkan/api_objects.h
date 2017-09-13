/*
 * Copyright 2017 Jacob Lifshay
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */
#ifndef VULKAN_API_OBJECTS_H_
#define VULKAN_API_OBJECTS_H_

#include "vulkan/vulkan.h"
#include "vulkan/vk_icd.h"
#include "vulkan/remove_xlib_macros.h"
#include "util/enum.h"
#include "util/string_view.h"
#include "util/variant.h"
#include "util/system_memory_info.h"
#include "util/constexpr_array.h"
#include <memory>
#include <cassert>
#include <chrono>
#include <limits>

namespace kazan
{
namespace vulkan
{
enum class Supported_extension
{
    Not_supported,
    KHR_surface,
    KHR_xcb_surface,
};

kazan_util_generate_enum_traits(Supported_extension,
                                Supported_extension::Not_supported,
                                Supported_extension::KHR_surface,
                                Supported_extension::KHR_xcb_surface);

typedef util::Enum_set<Supported_extension> Supported_extensions;

enum class Extension_scope
{
    Not_supported,
    Instance,
    Device,
};

constexpr Extension_scope get_extension_scope(Supported_extension extension) noexcept
{
    switch(extension)
    {
    case Supported_extension::Not_supported:
        return Extension_scope::Not_supported;
    case Supported_extension::KHR_surface:
        return Extension_scope::Instance;
    case Supported_extension::KHR_xcb_surface:
#ifdef VK_USE_PLATFORM_XCB_KHR
        return Extension_scope::Instance;
#else
        return Extension_scope::Not_supported;
#endif
    }
    assert(!"unknown extension");
    return Extension_scope::Not_supported;
}

constexpr VkExtensionProperties get_extension_properties(Supported_extension extension) noexcept
{
    switch(extension)
    {
    case Supported_extension::Not_supported:
        return {};
    case Supported_extension::KHR_surface:
        return {
            .extensionName = VK_KHR_SURFACE_EXTENSION_NAME,
            .specVersion = VK_KHR_SURFACE_SPEC_VERSION,
        };
    case Supported_extension::KHR_xcb_surface:
#ifdef VK_USE_PLATFORM_XCB_KHR
        return {
            .extensionName = VK_KHR_XCB_SURFACE_EXTENSION_NAME,
            .specVersion = VK_KHR_XCB_SURFACE_SPEC_VERSION,
        };
#else
        return {};
#endif
    }
    assert(!"unknown extension");
    return {};
}

constexpr std::size_t get_extension_count(Extension_scope scope) noexcept
{
    std::size_t retval = 0;
    for(auto extension : util::Enum_traits<Supported_extension>::values)
        if(get_extension_scope(extension) == scope)
            retval++;
    return retval;
}

template <Extension_scope Scope>
constexpr util::Constexpr_array<VkExtensionProperties, get_extension_count(Scope)>
    get_extensions() noexcept
{
    util::Constexpr_array<VkExtensionProperties, get_extension_count(Scope)> retval{};
    std::size_t index = 0;
    for(auto extension : util::Enum_traits<Supported_extension>::values)
        if(get_extension_scope(extension) == Scope)
            retval[index++] = get_extension_properties(extension);
    assert(index == retval.size());
    return retval;
}

constexpr Supported_extensions get_extension_dependencies(Supported_extension extension) noexcept
{
    switch(extension)
    {
    case Supported_extension::Not_supported:
        return {};
    case Supported_extension::KHR_surface:
        return {};
    case Supported_extension::KHR_xcb_surface:
        return {Supported_extension::KHR_surface};
    }
    assert(!"unknown extension");
    return {};
}

inline Supported_extension parse_extension_name(util::string_view name) noexcept
{
    if(name.empty())
        return Supported_extension::Not_supported;
    for(auto extension : util::Enum_traits<Supported_extension>::values)
    {
        if(extension == Supported_extension::Not_supported)
            continue;
        if(get_extension_properties(extension).extensionName == name)
            return extension;
    }
    return Supported_extension::Not_supported;
}

constexpr VkFormatProperties get_format_properties(VkFormat format) noexcept
{
    switch(format)
    {
    case VK_FORMAT_UNDEFINED:
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R4G4_UNORM_PACK8:
#warning implement VK_FORMAT_R4G4_UNORM_PACK8
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R4G4B4A4_UNORM_PACK16:
#warning implement VK_FORMAT_R4G4B4A4_UNORM_PACK16
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_B4G4R4A4_UNORM_PACK16:
#warning implement VK_FORMAT_B4G4R4A4_UNORM_PACK16
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R5G6B5_UNORM_PACK16:
#warning implement VK_FORMAT_R5G6B5_UNORM_PACK16
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_B5G6R5_UNORM_PACK16:
#warning implement VK_FORMAT_B5G6R5_UNORM_PACK16
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R5G5B5A1_UNORM_PACK16:
#warning implement VK_FORMAT_R5G5B5A1_UNORM_PACK16
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_B5G5R5A1_UNORM_PACK16:
#warning implement VK_FORMAT_B5G5R5A1_UNORM_PACK16
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_A1R5G5B5_UNORM_PACK16:
#warning implement VK_FORMAT_A1R5G5B5_UNORM_PACK16
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R8_UNORM:
#warning implement VK_FORMAT_R8_UNORM
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R8_SNORM:
#warning implement VK_FORMAT_R8_SNORM
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R8_USCALED:
#warning implement VK_FORMAT_R8_USCALED
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R8_SSCALED:
#warning implement VK_FORMAT_R8_SSCALED
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R8_UINT:
#warning implement VK_FORMAT_R8_UINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R8_SINT:
#warning implement VK_FORMAT_R8_SINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R8_SRGB:
#warning implement VK_FORMAT_R8_SRGB
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R8G8_UNORM:
#warning implement VK_FORMAT_R8G8_UNORM
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R8G8_SNORM:
#warning implement VK_FORMAT_R8G8_SNORM
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R8G8_USCALED:
#warning implement VK_FORMAT_R8G8_USCALED
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R8G8_SSCALED:
#warning implement VK_FORMAT_R8G8_SSCALED
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R8G8_UINT:
#warning implement VK_FORMAT_R8G8_UINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R8G8_SINT:
#warning implement VK_FORMAT_R8G8_SINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R8G8_SRGB:
#warning implement VK_FORMAT_R8G8_SRGB
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R8G8B8_UNORM:
#warning implement VK_FORMAT_R8G8B8_UNORM
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R8G8B8_SNORM:
#warning implement VK_FORMAT_R8G8B8_SNORM
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R8G8B8_USCALED:
#warning implement VK_FORMAT_R8G8B8_USCALED
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R8G8B8_SSCALED:
#warning implement VK_FORMAT_R8G8B8_SSCALED
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R8G8B8_UINT:
#warning implement VK_FORMAT_R8G8B8_UINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R8G8B8_SINT:
#warning implement VK_FORMAT_R8G8B8_SINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R8G8B8_SRGB:
#warning implement VK_FORMAT_R8G8B8_SRGB
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_B8G8R8_UNORM:
#warning implement VK_FORMAT_B8G8R8_UNORM
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_B8G8R8_SNORM:
#warning implement VK_FORMAT_B8G8R8_SNORM
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_B8G8R8_USCALED:
#warning implement VK_FORMAT_B8G8R8_USCALED
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_B8G8R8_SSCALED:
#warning implement VK_FORMAT_B8G8R8_SSCALED
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_B8G8R8_UINT:
#warning implement VK_FORMAT_B8G8R8_UINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_B8G8R8_SINT:
#warning implement VK_FORMAT_B8G8R8_SINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_B8G8R8_SRGB:
#warning implement VK_FORMAT_B8G8R8_SRGB
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R8G8B8A8_UNORM:
#warning implement VK_FORMAT_R8G8B8A8_UNORM
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R8G8B8A8_SNORM:
#warning implement VK_FORMAT_R8G8B8A8_SNORM
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R8G8B8A8_USCALED:
#warning implement VK_FORMAT_R8G8B8A8_USCALED
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R8G8B8A8_SSCALED:
#warning implement VK_FORMAT_R8G8B8A8_SSCALED
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R8G8B8A8_UINT:
#warning implement VK_FORMAT_R8G8B8A8_UINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R8G8B8A8_SINT:
#warning implement VK_FORMAT_R8G8B8A8_SINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R8G8B8A8_SRGB:
#warning implement VK_FORMAT_R8G8B8A8_SRGB
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_B8G8R8A8_UNORM:
#warning implement VK_FORMAT_B8G8R8A8_UNORM
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_B8G8R8A8_SNORM:
#warning implement VK_FORMAT_B8G8R8A8_SNORM
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_B8G8R8A8_USCALED:
#warning implement VK_FORMAT_B8G8R8A8_USCALED
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_B8G8R8A8_SSCALED:
#warning implement VK_FORMAT_B8G8R8A8_SSCALED
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_B8G8R8A8_UINT:
#warning implement VK_FORMAT_B8G8R8A8_UINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_B8G8R8A8_SINT:
#warning implement VK_FORMAT_B8G8R8A8_SINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_B8G8R8A8_SRGB:
#warning implement VK_FORMAT_B8G8R8A8_SRGB
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_A8B8G8R8_UNORM_PACK32:
#warning implement VK_FORMAT_A8B8G8R8_UNORM_PACK32
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_A8B8G8R8_SNORM_PACK32:
#warning implement VK_FORMAT_A8B8G8R8_SNORM_PACK32
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_A8B8G8R8_USCALED_PACK32:
#warning implement VK_FORMAT_A8B8G8R8_USCALED_PACK32
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_A8B8G8R8_SSCALED_PACK32:
#warning implement VK_FORMAT_A8B8G8R8_SSCALED_PACK32
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_A8B8G8R8_UINT_PACK32:
#warning implement VK_FORMAT_A8B8G8R8_UINT_PACK32
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_A8B8G8R8_SINT_PACK32:
#warning implement VK_FORMAT_A8B8G8R8_SINT_PACK32
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_A8B8G8R8_SRGB_PACK32:
#warning implement VK_FORMAT_A8B8G8R8_SRGB_PACK32
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_A2R10G10B10_UNORM_PACK32:
#warning implement VK_FORMAT_A2R10G10B10_UNORM_PACK32
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_A2R10G10B10_SNORM_PACK32:
#warning implement VK_FORMAT_A2R10G10B10_SNORM_PACK32
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_A2R10G10B10_USCALED_PACK32:
#warning implement VK_FORMAT_A2R10G10B10_USCALED_PACK32
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_A2R10G10B10_SSCALED_PACK32:
#warning implement VK_FORMAT_A2R10G10B10_SSCALED_PACK32
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_A2R10G10B10_UINT_PACK32:
#warning implement VK_FORMAT_A2R10G10B10_UINT_PACK32
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_A2R10G10B10_SINT_PACK32:
#warning implement VK_FORMAT_A2R10G10B10_SINT_PACK32
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_A2B10G10R10_UNORM_PACK32:
#warning implement VK_FORMAT_A2B10G10R10_UNORM_PACK32
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_A2B10G10R10_SNORM_PACK32:
#warning implement VK_FORMAT_A2B10G10R10_SNORM_PACK32
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_A2B10G10R10_USCALED_PACK32:
#warning implement VK_FORMAT_A2B10G10R10_USCALED_PACK32
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_A2B10G10R10_SSCALED_PACK32:
#warning implement VK_FORMAT_A2B10G10R10_SSCALED_PACK32
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_A2B10G10R10_UINT_PACK32:
#warning implement VK_FORMAT_A2B10G10R10_UINT_PACK32
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_A2B10G10R10_SINT_PACK32:
#warning implement VK_FORMAT_A2B10G10R10_SINT_PACK32
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R16_UNORM:
#warning implement VK_FORMAT_R16_UNORM
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R16_SNORM:
#warning implement VK_FORMAT_R16_SNORM
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R16_USCALED:
#warning implement VK_FORMAT_R16_USCALED
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R16_SSCALED:
#warning implement VK_FORMAT_R16_SSCALED
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R16_UINT:
#warning implement VK_FORMAT_R16_UINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R16_SINT:
#warning implement VK_FORMAT_R16_SINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R16_SFLOAT:
#warning implement VK_FORMAT_R16_SFLOAT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R16G16_UNORM:
#warning implement VK_FORMAT_R16G16_UNORM
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R16G16_SNORM:
#warning implement VK_FORMAT_R16G16_SNORM
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R16G16_USCALED:
#warning implement VK_FORMAT_R16G16_USCALED
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R16G16_SSCALED:
#warning implement VK_FORMAT_R16G16_SSCALED
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R16G16_UINT:
#warning implement VK_FORMAT_R16G16_UINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R16G16_SINT:
#warning implement VK_FORMAT_R16G16_SINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R16G16_SFLOAT:
#warning implement VK_FORMAT_R16G16_SFLOAT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R16G16B16_UNORM:
#warning implement VK_FORMAT_R16G16B16_UNORM
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R16G16B16_SNORM:
#warning implement VK_FORMAT_R16G16B16_SNORM
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R16G16B16_USCALED:
#warning implement VK_FORMAT_R16G16B16_USCALED
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R16G16B16_SSCALED:
#warning implement VK_FORMAT_R16G16B16_SSCALED
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R16G16B16_UINT:
#warning implement VK_FORMAT_R16G16B16_UINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R16G16B16_SINT:
#warning implement VK_FORMAT_R16G16B16_SINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R16G16B16_SFLOAT:
#warning implement VK_FORMAT_R16G16B16_SFLOAT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R16G16B16A16_UNORM:
#warning implement VK_FORMAT_R16G16B16A16_UNORM
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R16G16B16A16_SNORM:
#warning implement VK_FORMAT_R16G16B16A16_SNORM
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R16G16B16A16_USCALED:
#warning implement VK_FORMAT_R16G16B16A16_USCALED
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R16G16B16A16_SSCALED:
#warning implement VK_FORMAT_R16G16B16A16_SSCALED
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R16G16B16A16_UINT:
#warning implement VK_FORMAT_R16G16B16A16_UINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R16G16B16A16_SINT:
#warning implement VK_FORMAT_R16G16B16A16_SINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R16G16B16A16_SFLOAT:
#warning implement VK_FORMAT_R16G16B16A16_SFLOAT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R32_UINT:
#warning implement VK_FORMAT_R32_UINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R32_SINT:
#warning implement VK_FORMAT_R32_SINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R32_SFLOAT:
#warning implement VK_FORMAT_R32_SFLOAT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R32G32_UINT:
#warning implement VK_FORMAT_R32G32_UINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R32G32_SINT:
#warning implement VK_FORMAT_R32G32_SINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R32G32_SFLOAT:
#warning implement VK_FORMAT_R32G32_SFLOAT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R32G32B32_UINT:
#warning implement VK_FORMAT_R32G32B32_UINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R32G32B32_SINT:
#warning implement VK_FORMAT_R32G32B32_SINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R32G32B32_SFLOAT:
#warning implement VK_FORMAT_R32G32B32_SFLOAT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R32G32B32A32_UINT:
#warning implement VK_FORMAT_R32G32B32A32_UINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R32G32B32A32_SINT:
#warning implement VK_FORMAT_R32G32B32A32_SINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R32G32B32A32_SFLOAT:
#warning implement VK_FORMAT_R32G32B32A32_SFLOAT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R64_UINT:
#warning implement VK_FORMAT_R64_UINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R64_SINT:
#warning implement VK_FORMAT_R64_SINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R64_SFLOAT:
#warning implement VK_FORMAT_R64_SFLOAT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R64G64_UINT:
#warning implement VK_FORMAT_R64G64_UINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R64G64_SINT:
#warning implement VK_FORMAT_R64G64_SINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R64G64_SFLOAT:
#warning implement VK_FORMAT_R64G64_SFLOAT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R64G64B64_UINT:
#warning implement VK_FORMAT_R64G64B64_UINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R64G64B64_SINT:
#warning implement VK_FORMAT_R64G64B64_SINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R64G64B64_SFLOAT:
#warning implement VK_FORMAT_R64G64B64_SFLOAT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R64G64B64A64_UINT:
#warning implement VK_FORMAT_R64G64B64A64_UINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R64G64B64A64_SINT:
#warning implement VK_FORMAT_R64G64B64A64_SINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_R64G64B64A64_SFLOAT:
#warning implement VK_FORMAT_R64G64B64A64_SFLOAT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_B10G11R11_UFLOAT_PACK32:
#warning implement VK_FORMAT_B10G11R11_UFLOAT_PACK32
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_E5B9G9R9_UFLOAT_PACK32:
#warning implement VK_FORMAT_E5B9G9R9_UFLOAT_PACK32
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_D16_UNORM:
#warning implement VK_FORMAT_D16_UNORM
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_X8_D24_UNORM_PACK32:
#warning implement VK_FORMAT_X8_D24_UNORM_PACK32
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_D32_SFLOAT:
#warning implement VK_FORMAT_D32_SFLOAT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_S8_UINT:
#warning implement VK_FORMAT_S8_UINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_D16_UNORM_S8_UINT:
#warning implement VK_FORMAT_D16_UNORM_S8_UINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_D24_UNORM_S8_UINT:
#warning implement VK_FORMAT_D24_UNORM_S8_UINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_D32_SFLOAT_S8_UINT:
#warning implement VK_FORMAT_D32_SFLOAT_S8_UINT
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_BC1_RGB_UNORM_BLOCK:
#warning implement VK_FORMAT_BC1_RGB_UNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_BC1_RGB_SRGB_BLOCK:
#warning implement VK_FORMAT_BC1_RGB_SRGB_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_BC1_RGBA_UNORM_BLOCK:
#warning implement VK_FORMAT_BC1_RGBA_UNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_BC1_RGBA_SRGB_BLOCK:
#warning implement VK_FORMAT_BC1_RGBA_SRGB_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_BC2_UNORM_BLOCK:
#warning implement VK_FORMAT_BC2_UNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_BC2_SRGB_BLOCK:
#warning implement VK_FORMAT_BC2_SRGB_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_BC3_UNORM_BLOCK:
#warning implement VK_FORMAT_BC3_UNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_BC3_SRGB_BLOCK:
#warning implement VK_FORMAT_BC3_SRGB_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_BC4_UNORM_BLOCK:
#warning implement VK_FORMAT_BC4_UNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_BC4_SNORM_BLOCK:
#warning implement VK_FORMAT_BC4_SNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_BC5_UNORM_BLOCK:
#warning implement VK_FORMAT_BC5_UNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_BC5_SNORM_BLOCK:
#warning implement VK_FORMAT_BC5_SNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_BC6H_UFLOAT_BLOCK:
#warning implement VK_FORMAT_BC6H_UFLOAT_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_BC6H_SFLOAT_BLOCK:
#warning implement VK_FORMAT_BC6H_SFLOAT_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_BC7_UNORM_BLOCK:
#warning implement VK_FORMAT_BC7_UNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_BC7_SRGB_BLOCK:
#warning implement VK_FORMAT_BC7_SRGB_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK:
#warning implement VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK:
#warning implement VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK:
#warning implement VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK:
#warning implement VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK:
#warning implement VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK:
#warning implement VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_EAC_R11_UNORM_BLOCK:
#warning implement VK_FORMAT_EAC_R11_UNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_EAC_R11_SNORM_BLOCK:
#warning implement VK_FORMAT_EAC_R11_SNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_EAC_R11G11_UNORM_BLOCK:
#warning implement VK_FORMAT_EAC_R11G11_UNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_EAC_R11G11_SNORM_BLOCK:
#warning implement VK_FORMAT_EAC_R11G11_SNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ASTC_4x4_UNORM_BLOCK:
#warning implement VK_FORMAT_ASTC_4x4_UNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ASTC_4x4_SRGB_BLOCK:
#warning implement VK_FORMAT_ASTC_4x4_SRGB_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ASTC_5x4_UNORM_BLOCK:
#warning implement VK_FORMAT_ASTC_5x4_UNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ASTC_5x4_SRGB_BLOCK:
#warning implement VK_FORMAT_ASTC_5x4_SRGB_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ASTC_5x5_UNORM_BLOCK:
#warning implement VK_FORMAT_ASTC_5x5_UNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ASTC_5x5_SRGB_BLOCK:
#warning implement VK_FORMAT_ASTC_5x5_SRGB_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ASTC_6x5_UNORM_BLOCK:
#warning implement VK_FORMAT_ASTC_6x5_UNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ASTC_6x5_SRGB_BLOCK:
#warning implement VK_FORMAT_ASTC_6x5_SRGB_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ASTC_6x6_UNORM_BLOCK:
#warning implement VK_FORMAT_ASTC_6x6_UNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ASTC_6x6_SRGB_BLOCK:
#warning implement VK_FORMAT_ASTC_6x6_SRGB_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ASTC_8x5_UNORM_BLOCK:
#warning implement VK_FORMAT_ASTC_8x5_UNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ASTC_8x5_SRGB_BLOCK:
#warning implement VK_FORMAT_ASTC_8x5_SRGB_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ASTC_8x6_UNORM_BLOCK:
#warning implement VK_FORMAT_ASTC_8x6_UNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ASTC_8x6_SRGB_BLOCK:
#warning implement VK_FORMAT_ASTC_8x6_SRGB_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ASTC_8x8_UNORM_BLOCK:
#warning implement VK_FORMAT_ASTC_8x8_UNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ASTC_8x8_SRGB_BLOCK:
#warning implement VK_FORMAT_ASTC_8x8_SRGB_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ASTC_10x5_UNORM_BLOCK:
#warning implement VK_FORMAT_ASTC_10x5_UNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ASTC_10x5_SRGB_BLOCK:
#warning implement VK_FORMAT_ASTC_10x5_SRGB_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ASTC_10x6_UNORM_BLOCK:
#warning implement VK_FORMAT_ASTC_10x6_UNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ASTC_10x6_SRGB_BLOCK:
#warning implement VK_FORMAT_ASTC_10x6_SRGB_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ASTC_10x8_UNORM_BLOCK:
#warning implement VK_FORMAT_ASTC_10x8_UNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ASTC_10x8_SRGB_BLOCK:
#warning implement VK_FORMAT_ASTC_10x8_SRGB_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ASTC_10x10_UNORM_BLOCK:
#warning implement VK_FORMAT_ASTC_10x10_UNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ASTC_10x10_SRGB_BLOCK:
#warning implement VK_FORMAT_ASTC_10x10_SRGB_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ASTC_12x10_UNORM_BLOCK:
#warning implement VK_FORMAT_ASTC_12x10_UNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ASTC_12x10_SRGB_BLOCK:
#warning implement VK_FORMAT_ASTC_12x10_SRGB_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ASTC_12x12_UNORM_BLOCK:
#warning implement VK_FORMAT_ASTC_12x12_UNORM_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_ASTC_12x12_SRGB_BLOCK:
#warning implement VK_FORMAT_ASTC_12x12_SRGB_BLOCK
        return {
            .linearTilingFeatures = 0, .optimalTilingFeatures = 0, .bufferFeatures = 0,
        };
    case VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG:
    case VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG:
    case VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG:
    case VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG:
    case VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG:
    case VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG:
    case VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG:
    case VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG:
    case VK_FORMAT_RANGE_SIZE:
    case VK_FORMAT_MAX_ENUM:
        break;
    }
    assert(!"invalid format enum");
    return {};
}

template <typename Object_type, typename Vulkan_handle_type>
struct Vulkan_dispatchable_object
{
    VK_LOADER_DATA vulkan_loader_data{.loaderMagic = ICD_LOADER_MAGIC};
    typedef Vulkan_handle_type Vulkan_handle;
    typedef Object_type Object;
    static Object_type *from_handle(Vulkan_handle_type v) noexcept
    {
        return static_cast<Object_type *>(reinterpret_cast<Vulkan_dispatchable_object *>(v));
    }
    static std::unique_ptr<Object_type> move_from_handle(Vulkan_handle_type v) noexcept
    {
        return std::unique_ptr<Object_type>(from_handle(v));
    }
};

template <typename Object_type>
typename std::
    enable_if<std::is_base_of<Vulkan_dispatchable_object<Object_type,
                                                         typename Object_type::Vulkan_handle>,
                              Object_type>::value,
              typename Object_type::Vulkan_handle>::type
    to_handle(Object_type *object) noexcept
{
    return reinterpret_cast<typename Object_type::Vulkan_handle>(
        static_cast<Vulkan_dispatchable_object<Object_type, typename Object_type::Vulkan_handle> *>(
            object));
}

template <typename Object_type>
decltype(to_handle(static_cast<Object_type *>(nullptr))) move_to_handle(
    std::unique_ptr<Object_type> v) noexcept
{
    return to_handle(v.release());
}

struct Vulkan_instance;

struct Vulkan_physical_device
    : public Vulkan_dispatchable_object<Vulkan_physical_device, VkPhysicalDevice>
{
    Vulkan_instance &instance;
    VkPhysicalDeviceProperties properties;
    static constexpr std::size_t queue_family_property_count = 1;
    VkQueueFamilyProperties queue_family_properties[queue_family_property_count];
    VkPhysicalDeviceMemoryProperties memory_properties;
    VkPhysicalDeviceFeatures features;
    static VkDeviceSize calculate_heap_size() noexcept
    {
        std::uintmax_t total_usable_ram = util::System_memory_info::get().total_usable_ram;
        constexpr std::uintmax_t transition_memory_size = 4ULL << 30; // 4 GiB
        std::uintmax_t heap_size;
        if(total_usable_ram >= transition_memory_size)
            heap_size = total_usable_ram * 3 / 4;
        else
            heap_size = total_usable_ram / 2;
        if(heap_size > std::numeric_limits<VkDeviceSize>::max())
            heap_size = std::numeric_limits<VkDeviceSize>::max();
        return heap_size;
    }
    Vulkan_physical_device(Vulkan_instance &instance) noexcept
        : instance(instance),
          properties{
              .apiVersion = VK_MAKE_VERSION(1, 0, VK_HEADER_VERSION),
              .driverVersion = 0,
              .vendorID = 0x10003UL,
              .deviceID = 0,
              .deviceType = VK_PHYSICAL_DEVICE_TYPE_CPU,
              .deviceName = "Kazan Software Renderer",
#warning calculate the correct value of pipelineCacheUUID as the hash of the target cpu info and the hashed source code
              .pipelineCacheUUID = {},
              .limits =
                  {
                      .maxImageDimension1D = 1UL << 20,
                      .maxImageDimension2D = 1UL << 20,
                      .maxImageDimension3D = 1UL << 20,
                      .maxImageDimensionCube = 1UL << 20,
                      .maxImageArrayLayers = static_cast<std::uint32_t>(-1),
                      .maxTexelBufferElements = static_cast<std::uint32_t>(-1),
                      .maxUniformBufferRange = static_cast<std::uint32_t>(-1),
                      .maxStorageBufferRange = static_cast<std::uint32_t>(-1),
                      .maxPushConstantsSize = static_cast<std::uint32_t>(-1),
                      .maxMemoryAllocationCount = static_cast<std::uint32_t>(-1),
                      .maxSamplerAllocationCount = static_cast<std::uint32_t>(-1),
                      .bufferImageGranularity = 1,
                      .sparseAddressSpaceSize = 0,
                      .maxBoundDescriptorSets = static_cast<std::uint32_t>(-1),
                      .maxPerStageDescriptorSamplers = static_cast<std::uint32_t>(-1),
                      .maxPerStageDescriptorUniformBuffers = static_cast<std::uint32_t>(-1),
                      .maxPerStageDescriptorStorageBuffers = static_cast<std::uint32_t>(-1),
                      .maxPerStageDescriptorSampledImages = static_cast<std::uint32_t>(-1),
                      .maxPerStageDescriptorStorageImages = static_cast<std::uint32_t>(-1),
                      .maxPerStageDescriptorInputAttachments = static_cast<std::uint32_t>(-1),
                      .maxPerStageResources = static_cast<std::uint32_t>(-1),
                      .maxDescriptorSetSamplers = static_cast<std::uint32_t>(-1),
                      .maxDescriptorSetUniformBuffers = static_cast<std::uint32_t>(-1),
                      .maxDescriptorSetUniformBuffersDynamic = static_cast<std::uint32_t>(-1),
                      .maxDescriptorSetStorageBuffers = static_cast<std::uint32_t>(-1),
                      .maxDescriptorSetStorageBuffersDynamic = static_cast<std::uint32_t>(-1),
                      .maxDescriptorSetSampledImages = static_cast<std::uint32_t>(-1),
                      .maxDescriptorSetStorageImages = static_cast<std::uint32_t>(-1),
                      .maxDescriptorSetInputAttachments = static_cast<std::uint32_t>(-1),
                      .maxVertexInputAttributes = static_cast<std::uint32_t>(-1),
                      .maxVertexInputBindings = static_cast<std::uint32_t>(-1),
                      .maxVertexInputAttributeOffset = static_cast<std::uint32_t>(-1),
                      .maxVertexInputBindingStride = static_cast<std::uint32_t>(-1),
                      .maxVertexOutputComponents = static_cast<std::uint32_t>(-1),
                      .maxTessellationGenerationLevel = 0,
                      .maxTessellationPatchSize = 0,
                      .maxTessellationControlPerVertexInputComponents = 0,
                      .maxTessellationControlPerVertexOutputComponents = 0,
                      .maxTessellationControlPerPatchOutputComponents = 0,
                      .maxTessellationControlTotalOutputComponents = 0,
                      .maxTessellationEvaluationInputComponents = 0,
                      .maxTessellationEvaluationOutputComponents = 0,
                      .maxGeometryShaderInvocations = 0,
                      .maxGeometryInputComponents = 0,
                      .maxGeometryOutputComponents = 0,
                      .maxGeometryOutputVertices = 0,
                      .maxGeometryTotalOutputComponents = 0,
                      .maxFragmentInputComponents = static_cast<std::uint32_t>(-1),
                      .maxFragmentOutputAttachments = static_cast<std::uint32_t>(-1),
                      .maxFragmentDualSrcAttachments = 0,
                      .maxFragmentCombinedOutputResources = static_cast<std::uint32_t>(-1),
                      .maxComputeSharedMemorySize = static_cast<std::uint32_t>(-1),
                      .maxComputeWorkGroupCount =
                          {
                              static_cast<std::uint32_t>(-1),
                              static_cast<std::uint32_t>(-1),
                              static_cast<std::uint32_t>(-1),
                          },
                      .maxComputeWorkGroupInvocations = static_cast<std::uint32_t>(-1),
                      .maxComputeWorkGroupSize =
                          {
                              static_cast<std::uint32_t>(-1),
                              static_cast<std::uint32_t>(-1),
                              static_cast<std::uint32_t>(-1),
                          },
                      .subPixelPrecisionBits = 16,
                      .subTexelPrecisionBits = 8,
                      .mipmapPrecisionBits = 8,
                      .maxDrawIndexedIndexValue = static_cast<std::uint32_t>(-1),
                      .maxDrawIndirectCount = static_cast<std::uint32_t>(-1),
                      .maxSamplerLodBias = 65536.0f,
                      .maxSamplerAnisotropy = 1,
                      .maxViewports = 1,
                      .maxViewportDimensions =
                          {
                              1UL << 20, 1UL << 20,
                          },
                      .viewportBoundsRange =
                          {
                              static_cast<float>(-1) * (1UL << 21), 1UL << 21,
                          },
                      .viewportSubPixelBits = 16,
                      .minMemoryMapAlignment = 64,
                      .minTexelBufferOffsetAlignment = alignof(std::max_align_t),
                      .minUniformBufferOffsetAlignment = alignof(std::max_align_t),
                      .minStorageBufferOffsetAlignment = alignof(std::max_align_t),
                      .minTexelOffset = std::numeric_limits<std::int32_t>::min(),
                      .maxTexelOffset = std::numeric_limits<std::int32_t>::max(),
                      .minTexelGatherOffset = 0,
                      .maxTexelGatherOffset = 0,
                      .minInterpolationOffset = 0,
                      .maxInterpolationOffset = 0,
                      .subPixelInterpolationOffsetBits = 0,
                      .maxFramebufferWidth = 1UL << 20,
                      .maxFramebufferHeight = 1UL << 20,
                      .maxFramebufferLayers = static_cast<std::uint32_t>(-1),
#warning fix up sample counts after adding multisampling
                      .framebufferColorSampleCounts = VK_SAMPLE_COUNT_1_BIT,
                      .framebufferDepthSampleCounts = VK_SAMPLE_COUNT_1_BIT,
                      .framebufferStencilSampleCounts = VK_SAMPLE_COUNT_1_BIT,
                      .framebufferNoAttachmentsSampleCounts = VK_SAMPLE_COUNT_1_BIT,
                      .maxColorAttachments = static_cast<std::uint32_t>(-1),
                      .sampledImageColorSampleCounts = VK_SAMPLE_COUNT_1_BIT,
                      .sampledImageIntegerSampleCounts = VK_SAMPLE_COUNT_1_BIT,
                      .sampledImageDepthSampleCounts = VK_SAMPLE_COUNT_1_BIT,
                      .sampledImageStencilSampleCounts = VK_SAMPLE_COUNT_1_BIT,
                      .storageImageSampleCounts = VK_SAMPLE_COUNT_1_BIT,
                      .maxSampleMaskWords = 1,
                      .timestampComputeAndGraphics = true,
                      .timestampPeriod =
                          std::chrono::duration_cast<std::chrono::duration<double, std::nano>>(
                              std::chrono::steady_clock::duration(1))
                              .count(),
                      .maxClipDistances = 0,
                      .maxCullDistances = 0,
                      .maxCombinedClipAndCullDistances = 0,
                      .discreteQueuePriorities = 2,
                      .pointSizeRange =
                          {
                              1, 1,
                          },
                      .lineWidthRange =
                          {
                              1, 1,
                          },
                      .pointSizeGranularity = 0,
                      .lineWidthGranularity = 0,
#warning update strictLines when the line rasterizer is implemented
                      .strictLines = true,
                      .standardSampleLocations = true,
                      .optimalBufferCopyOffsetAlignment = 16,
                      .optimalBufferCopyRowPitchAlignment = 16,
                      .nonCoherentAtomSize = 1,
                  },
              .sparseProperties =
                  {
#warning update upon implementation of sparse memory
                      .residencyStandard2DBlockShape = false,
                      .residencyStandard2DMultisampleBlockShape = false,
                      .residencyStandard3DBlockShape = false,
                      .residencyAlignedMipSize = false,
                      .residencyNonResidentStrict = false,
                  },
          },
          queue_family_properties{
              {
                  .queueFlags = VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT,
                  .queueCount = 1,
                  .timestampValidBits = std::numeric_limits<std::chrono::steady_clock::rep>::digits
                                        + 1, // 1 extra for sign bit
                  .minImageTransferGranularity =
                      {
                          1, 1, 1,
                      },
              },
          },
          memory_properties{
              .memoryTypeCount = 1,
              .memoryTypes =
                  {
                      {
                          .propertyFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
                                           | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
                                           | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
                                           | VK_MEMORY_PROPERTY_HOST_CACHED_BIT,
                          .heapIndex = 0,
                      },
                  },
              .memoryHeapCount = 1,
              .memoryHeaps =
                  {
                      {
                          .size = calculate_heap_size(), .flags = VK_MEMORY_HEAP_DEVICE_LOCAL_BIT,
                      },
                  },
          },
          features{
#warning implement robust buffer access
              .robustBufferAccess = false,
              .fullDrawIndexUint32 = true,
              .imageCubeArray = false,
              .independentBlend = true,
              .geometryShader = false,
              .tessellationShader = false,
              .sampleRateShading = false,
              .dualSrcBlend = false,
              .logicOp = false,
              .multiDrawIndirect = true,
              .drawIndirectFirstInstance = true,
              .depthClamp = false,
              .depthBiasClamp = false,
              .fillModeNonSolid = false,
              .depthBounds = false,
              .wideLines = false,
              .largePoints = false,
              .alphaToOne = false,
              .multiViewport = false,
              .samplerAnisotropy = false,
              .textureCompressionETC2 = false,
              .textureCompressionASTC_LDR = false,
              .textureCompressionBC = false,
              .occlusionQueryPrecise = false,
              .pipelineStatisticsQuery = false,
              .vertexPipelineStoresAndAtomics = false,
              .fragmentStoresAndAtomics = false,
              .shaderTessellationAndGeometryPointSize = false,
              .shaderImageGatherExtended = false,
              .shaderStorageImageExtendedFormats = false,
              .shaderStorageImageMultisample = false,
              .shaderStorageImageReadWithoutFormat = false,
              .shaderStorageImageWriteWithoutFormat = false,
              .shaderUniformBufferArrayDynamicIndexing = true,
              .shaderSampledImageArrayDynamicIndexing = true,
              .shaderStorageBufferArrayDynamicIndexing = true,
              .shaderStorageImageArrayDynamicIndexing = true,
              .shaderClipDistance = false,
              .shaderCullDistance = false,
              .shaderFloat64 = false,
              .shaderInt64 = true,
              .shaderInt16 = false,
              .shaderResourceResidency = false,
              .shaderResourceMinLod = false,
              .sparseBinding = false,
              .sparseResidencyBuffer = false,
              .sparseResidencyImage2D = false,
              .sparseResidencyImage3D = false,
              .sparseResidency2Samples = false,
              .sparseResidency4Samples = false,
              .sparseResidency8Samples = false,
              .sparseResidency16Samples = false,
              .sparseResidencyAliased = false,
              .variableMultisampleRate = false,
              .inheritedQueries = false,
          }
    {
    }
};

struct Vulkan_instance : public Vulkan_dispatchable_object<Vulkan_instance, VkInstance>
{
    Vulkan_instance(const Vulkan_instance &) = delete;
    Vulkan_instance &operator=(const Vulkan_instance &) = delete;

    struct App_info
    {
        std::string application_name;
        std::uint32_t application_version;
        std::string engine_name;
        std::uint32_t engine_version;
        std::uint32_t api_version;
        App_info(std::string application_name,
                 std::uint32_t application_version,
                 std::string engine_name,
                 std::uint32_t engine_version,
                 std::uint32_t api_version) noexcept
            : application_name(std::move(application_name)),
              application_version(application_version),
              engine_name(std::move(engine_name)),
              engine_version(engine_version),
              api_version(api_version)
        {
        }
        explicit App_info(const VkApplicationInfo &application_info)
            : application_name(
                  application_info.pApplicationName ? application_info.pApplicationName : ""),
              application_version(application_info.applicationVersion),
              engine_name(application_info.pEngineName ? application_info.pEngineName : ""),
              engine_version(application_info.engineVersion),
              api_version(application_info.apiVersion)
        {
            assert(application_info.sType == VK_STRUCTURE_TYPE_APPLICATION_INFO);
        }
        App_info() noexcept : application_name(),
                              application_version(),
                              engine_name(),
                              engine_version(),
                              api_version()
        {
        }
    };
    App_info app_info;
    Supported_extensions extensions;
    Vulkan_physical_device physical_device;
    Vulkan_instance(App_info app_info, Supported_extensions extensions) noexcept
        : app_info(std::move(app_info)),
          extensions(std::move(extensions)),
          physical_device(*this)
    {
    }
    static util::variant<std::unique_ptr<Vulkan_instance>, VkResult> create(
        const VkInstanceCreateInfo &create_info);
#warning finish implementing Vulkan_instance
};

struct Vulkan_device : public Vulkan_dispatchable_object<Vulkan_device, VkDevice>
{
    struct Queue
    {
    };
    Vulkan_instance &instance;
    Vulkan_physical_device &physical_device;
    VkPhysicalDeviceFeatures enabled_features;
    static constexpr std::size_t queue_count = 1;
    Queue queues[queue_count];
    Supported_extensions extensions; // includes both device and instance extensions
    explicit Vulkan_device(Vulkan_physical_device &physical_device,
                           const VkPhysicalDeviceFeatures &enabled_features,
                           const Supported_extensions &extensions) noexcept
        : instance(physical_device.instance),
          physical_device(physical_device),
          enabled_features(enabled_features),
          extensions(extensions)
    {
    }
    void wait_idle()
    {
#warning implement Vulkan_device::wait_idle
    }
    static util::variant<std::unique_ptr<Vulkan_device>, VkResult> create(
        Vulkan_physical_device &physical_device, const VkDeviceCreateInfo &create_info);
};
}
}

#endif // VULKAN_API_OBJECTS_H_
