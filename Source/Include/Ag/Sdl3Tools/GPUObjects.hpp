//! @file Ag/Sdl3Tools/GPUObjects.hpp
//! @brief The declaration of wrappers for GPU-related SDL 3 Data types.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_SDL3_TOOLS_GPU_OBJECTS_HPP__
#define __AG_SDL3_TOOLS_GPU_OBJECTS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <vector>

#include "Ag/Core/String.hpp"
#include "Ag/Sdl3Tools/PropertySet.hpp"
#include "Ag/Sdl3Tools/WrapperTypes.hpp"

namespace Ag {
namespace SDL3 {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
class Window;

namespace GPU {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class Device;
class Swapchain;

//! @brief A wrapper synchronisation primitive used when submitting command
//! buffers to GPUs for processing.
class Fence
{
public:
    // Construction/Destruction
    Fence();
    Fence(const Fence &) = delete;
    Fence(Fence &&rhs) noexcept;
    Fence(SDL_GPUDevice *parentDevice, SDL_GPUFence *fence);
    ~Fence();

    // Accessors
    bool isBound() const;
    bool isSignalled() const;
    SDL_GPUFence *get() const;

    // Operations
    bool tryWait() const noexcept;
    void wait() const;

    void release() noexcept;

    Fence &operator=(const Fence &) = delete;
    Fence &operator=(Fence &&rhs) noexcept;
private:
    // Internal Functions
    SDL_GPUFence *verifyAccess(utf8_cptr_t operation) const;

    // Internal Fields
    SDL_GPUDevice *_parentDevice;
    SDL_GPUFence *_fence;
};

//! @brief A wrapper for a block of system memory representing the contents of a
//! GPU transfer buffer.
class TransferMapping
{
public:
    // Construction/Destruction
    TransferMapping();
    TransferMapping(SDL_GPUDevice *parentDevice, SDL_GPUTransferBuffer *buffer,
                    void *mapping, uint32_t size);
    TransferMapping(const TransferMapping &) = delete;
    TransferMapping(TransferMapping &&rhs) noexcept;
    ~TransferMapping();

    // Accessors
    bool isMapped() const;
    uint32_t getSize() const;
    void *getMapping() const;

    //! @brief Gets a pointer to the mapped block with a useful data type.
    //! @tparam T The data type of the array of elements in the buffer.
    //! @param[out] count Receives the maximum count of elements in the buffer.
    //! @return A pointer to the first element.
    template<typename T> T *getTypedMapping(size_t &count) const
    {
        count = _size / sizeof(T);

        return reinterpret_cast<T *>(_mappedBlock);
    }

    // Operations
    void unmap();
    TransferMapping &operator=(const TransferMapping &) = delete;
    TransferMapping &operator=(TransferMapping &&rhs) noexcept;
private:
    // Internal Fields
    SDL_GPUDevice *_parentDevice;
    SDL_GPUTransferBuffer *_buffer;
    void *_mappedBlock;
    uint32_t _size;
};

//! @brief A wrapper for a system memory buffer used to transfer data to or
//! from GPU memory.
class TransferBuffer
{
public:
    // Construction/Destruction
    TransferBuffer();
    TransferBuffer(SDL_GPUDevice *parentDevice, SDL_GPUTransferBuffer *buffer,
                   uint32_t size);
    TransferBuffer(const TransferBuffer &) = delete;
    TransferBuffer(TransferBuffer &&rhs) noexcept;
    ~TransferBuffer();

    // Accessors
    bool isBound() const;
    uint32_t getSize() const;

    // Operations
    TransferMapping map(bool cycle) const;
    void release();
    TransferBuffer &operator=(const TransferBuffer &) = delete;
    TransferBuffer &operator=(TransferBuffer &&rhs) noexcept;
    SDL_GPUTransferBuffer *verifyAccess(utf8_cptr_t operation) const;
private:
    // Internal Fields
    SDL_GPUDevice *_parentDevice;
    SDL_GPUTransferBuffer *_buffer;
    uint32_t _size;
};

//! @brief A wrapper for a GPU memory buffer used to hold vertex or index data.
class ResourceBuffer
{
public:
    // Construction/Destruction
    ResourceBuffer();
    ResourceBuffer(SDL_GPUDevice *parentDevice, SDL_GPUBuffer *buffer,
                   uint32_t size);
    ResourceBuffer(const ResourceBuffer &) = delete;
    ResourceBuffer(ResourceBuffer &&rhs) noexcept;
    ~ResourceBuffer();

    // Accessors
    bool isBound() const;
    uint32_t getSize() const;

    // Operations
    void release();
    ResourceBuffer &operator=(const ResourceBuffer &) = delete;
    ResourceBuffer &operator=(ResourceBuffer &&rhs) noexcept;
    SDL_GPUBuffer *verifyAccess(utf8_cptr_t operation) const;
private:
    // Internal Fields
    SDL_GPUDevice *_parentDevice;
    SDL_GPUBuffer *_buffer;
    uint32_t _size;
};

//! @brief A wrapper for a GPU texture resource.
class Texture
{
friend class CopyPass;
public:
    // Construction/Destruction
    Texture();
    Texture(SDL_GPUDevice *parentDevice, SDL_GPUTexture *texture, bool releaseOnDestroy = true);
    Texture(const Texture &) = delete;
    Texture(Texture &&rhs) noexcept;
    ~Texture();

    // Accessors
    bool isBound() const;
    SDL_GPUTexture *get() const;

    // Operations
    void release();
    Texture &operator=(const Texture &) = delete;
    Texture &operator=(Texture &&rhs) noexcept;
private:
    // Internal Functions
    SDL_GPUTexture *verifyAccess(utf8_cptr_t operation) const;

    // Internal Fields
    SDL_GPUDevice *_parentDevice;
    SDL_GPUTexture *_texture;
    bool _releaseOnDestroy;
};

//! @brief A wrapper for a GPU shader program.
class Shader
{
public:
    // Construction/Destruction
    Shader();
    Shader(SDL_GPUDevice *device, SDL_GPUShader *shader);
    Shader(const Shader &) = delete;
    Shader(Shader &&rhs) noexcept;
    ~Shader();

    // Accessors
    bool isBound() const;
    SDL_GPUShader *get() const;

    // Operations
    void release();
    Shader &operator=(const Shader &) = delete;
    Shader &operator=(Shader &&rhs) noexcept;

private:
    // Internal Fields
    SDL_GPUDevice *_parentDevice;
    SDL_GPUShader *_shader;
};

//! @brief An object which specifies helps build the parameters of a shader.
class ShaderBuilder
{
public:
    // Construction/Destruction
    ShaderBuilder() = delete;
    ShaderBuilder(const Device &device,
                  SDL_GPUShaderFormat format);

    //! @brief Creates an object to help build a shader object.
    //! @tparam T The data type of the raw shader program data.
    //! @tparam U The count of elements in the shader program data.
    //! @param[in] device The device to create the shaders on.
    //! @param[in] code An array containing the raw shader program.
    //! @param[in] stage The stage of the pipeline the shader is intended to be
    //! used in.
    //! @param[in] format The format of the shader.
    template<typename T, size_t U>
    ShaderBuilder(const Device &device,
                  const T(&code)[U],
                  SDL_GPUShaderStage stage,
                  SDL_GPUShaderFormat format) :
        _device(device._device),
        _defaultFormat(format)
    {
        beginShader(reinterpret_cast<const uint8_t *>(values),
                    U * sizeof(T), stage, format);
    }

    // Accessors
    // TODO: Add accessors for binding count values.

    // Operations
    //! @brief Resets the object to build a new shader object.
    //! @tparam T The data type of the raw shader program data.
    //! @tparam U The count of elements in the shader program data.
    //! @param[in] code An array containing the raw shader program.
    //! @param[in] stage The stage of the pipeline the shader is intended to be
    //! used in.
    //! @param[in] format The format of the shader. If SDL_GPU_SHADERFORMAT_INVALID
    //! is specified, the default format will be used.
    template<typename T, size_t U>
    void begin(const T(&code)[U], SDL_GPUShaderStage stage,
               SDL_GPUShaderFormat format = SDL_GPU_SHADERFORMAT_INVALID)
    {
        beginShader(reinterpret_cast<const uint8_t *>(code),
                    U * sizeof(T), stage, format);
    }

    void beginShader(const uint8_t *code, size_t byteCount,
                     SDL_GPUShaderStage stage,
                     SDL_GPUShaderFormat format = SDL_GPU_SHADERFORMAT_INVALID);

    // TODO: Allow binding count values to be specified as optional parameters?
    Shader createShader() const;
private:
    // Internal Fields
    SDL_GPUShaderCreateInfo _info;
    SDL_GPUDevice *_device;
    SDL_GPUShaderFormat _defaultFormat;
};

//! @brief A wrapper for a GPU graphics pipeline.
class GraphicsPipeline
{
public:
    // Construction/Destruction
    GraphicsPipeline();
    GraphicsPipeline(const GraphicsPipeline &) = delete;
    GraphicsPipeline(GraphicsPipeline &&rhs) noexcept;
    GraphicsPipeline(SDL_GPUDevice *parentDevice, SDL_GPUGraphicsPipeline *pipeline);
    ~GraphicsPipeline();

    // Accessors
    bool isBound() const;

    // Operations
    void release() noexcept;

    GraphicsPipeline &operator=(const GraphicsPipeline &) = delete;
    GraphicsPipeline &operator=(GraphicsPipeline &&rhs) noexcept;
    SDL_GPUGraphicsPipeline *verifyAccess(utf8_cptr_t operation) const;
private:
    // Internal Fields
    SDL_GPUDevice *_parentDevice;
    SDL_GPUGraphicsPipeline *_pipeline;
};

using SDL_GPUVertexAttributeVector = std::vector<SDL_GPUVertexAttribute>;

//! @brief An object which builds a description of a vertex buffer.
class VertexDescriptionBuilder
{
public:
    // Construction/Destruction
    VertexDescriptionBuilder(size_t pitch = 0, uint32_t bufferSlot = 0, uint32_t locationOffset = 0);

    // Operations
    void makeInstanced();
    void beginNextBuffer(size_t pitch = 0);
    uint32_t addAttribute(SDL_GPUVertexElementFormat format,
                          size_t offset = SIZE_MAX,
                          uint32_t location = UINT32_MAX);

    const SDL_GPUVertexAttributeVector &build(SDL_GPUVertexBufferDescription &desc) const;
private:
    // Internal Fields
    SDL_GPUVertexBufferDescription _desc;
    SDL_GPUVertexAttributeVector _attributes;
    uint32_t _locationOffset;
};

//! @brief An object which incrementally builds up the properties of a GPU
//! graphics pipeline to be constructed.
class GraphicsPipelineBuilder
{
public:
    // Construction/Destruction
    GraphicsPipelineBuilder(const Device &gpu);

    // Accessors

    // Operations
    void begin(const Shader &vertex, const Shader &fragment,
               SDL_GPUPrimitiveType primitiveType);
    uint32_t addRenderTarget(const Swapchain &swapchain);
    uint32_t addVertexBufferDescription(const VertexDescriptionBuilder &builder);

    GraphicsPipeline createPipeline() const;
private:
    // Internal Functions
    void reset();

    // Internal Fields
    SDL_GPUGraphicsPipelineCreateInfo _info;
    SDL_GPUDevice *_device;
    std::vector<SDL_GPUColorTargetDescription> _colourTargets;
    std::vector<SDL_GPUVertexBufferDescription> _bufferDescriptions;
    SDL_GPUVertexAttributeVector _vertexAttributes;
};

//! @brief A wrapper for a GPU copy pass within a command buffer.
class CopyPass
{
public:
    // Construction/Destruction
    CopyPass();
    CopyPass(SDL_GPUCopyPass *CopyPass);
    CopyPass(const CopyPass &) = delete;
    CopyPass(CopyPass &&rhs) noexcept;
    ~CopyPass();

    // Accessors
    bool isBound() const;

    // Operations
    void endPass();
    CopyPass &operator=(const CopyPass &) = delete;
    CopyPass &operator=(CopyPass &&rhs) noexcept;
    void uploadToBuffer(const ResourceBuffer &destBuffer, uint32_t destOffset,
                        const TransferBuffer &sourceBuffer, uint32_t sourceOffset,
                        uint32_t size, bool cycle) const;
    //void uploadToTexture(const Texture &destTexture)
private:
    // Internal Functions
    SDL_GPUCopyPass *verifyAccess(utf8_cptr_t operation) const;

    // Internal Fields
    SDL_GPUCopyPass *_copyPass;
};

//! @brief An alias for a vector of GPU buffer binding descriptions.
using BufferBindingCollection = std::vector<SDL_GPUBufferBinding>;

//! @brief An object which collects buffers to be bound to a graphics pipeline.
class VertexBufferBindingBuilder
{
public:
    // Construction/Destruction
    VertexBufferBindingBuilder(uint32_t firstSlot = 0);

    // Accessors
    uint32_t getFirstSlot() const;

    // Operations
    void begin(uint32_t firstSlot = 0);
    void addBinding(const ResourceBuffer &buffer, uint32_t offset = 0);
    const BufferBindingCollection &getBindings() const;
private:
    // Internal Fields
    BufferBindingCollection _bindings;
    uint32_t _firstSlot;
};

//! @brief A wrapper for an object which samples textures in a GPU pipeline.
class Sampler
{
public:
    // Construction/Destruction
    Sampler();
    Sampler(SDL_GPUDevice *parentDevice, SDL_GPUSampler *sampler);
    Sampler(const Sampler &) = delete;
    Sampler(Sampler &&rhs) noexcept;
    ~Sampler();

    // Accessors
    bool isBound() const;

    // Operations
    void release();
    Sampler &operator=(const Sampler &) = delete;
    Sampler &operator=(Sampler &&rhs) noexcept;
    SDL_GPUSampler *verifyAccess(utf8_cptr_t operation) const;
private:
    // Internal Fields
    SDL_GPUDevice *_parentDevice;
    SDL_GPUSampler *_sampler;
};

//! @brief A wrapper for a GPU render pass within a command buffer.
class RenderPass
{
public:
    // Construction/Destruction
    RenderPass();
    RenderPass(SDL_GPURenderPass *renderPass);
    RenderPass(const RenderPass &) = delete;
    RenderPass(RenderPass &&rhs) noexcept;
    ~RenderPass();

    // Accessors
    bool isBound() const;

    // Operations
    void bindPipeline(const GraphicsPipeline &pipeline) const;
    void bindVertexBuffers(const VertexBufferBindingBuilder &bindings) const;
    void drawPrimitives(uint32_t vertexCount, uint32_t instanceCount = 1,
                        uint32_t firstVertex = 0, uint32_t firstInstance = 0) const;
    void endPass();
    RenderPass &operator=(const RenderPass &) = delete;
    RenderPass &operator=(RenderPass &&rhs) noexcept;
private:
    // Internal Functions
    SDL_GPURenderPass *verifyAccess(utf8_cptr_t operation) const;

    // Internal Fields
    SDL_GPURenderPass *_renderPass;
};

//! @brief A wrapper for a GPU command buffer object.
class CommandBuffer
{
public:
    // Construction/Destruction
    CommandBuffer();
    CommandBuffer(const CommandBuffer &) = delete;
    CommandBuffer(CommandBuffer &&rhs) noexcept;
    CommandBuffer(SDL_GPUDevice *device, SDL_GPUCommandBuffer *commandBuffer);
    ~CommandBuffer();

    // Accessors
    bool isBound() const;

    // Operations
    void cancel();
    void submit();
    void submitAndWait();
    Fence submitAndAcquireFence();
    Texture waitAndAcquireSwapchainTexture(const Window &window, uint32_t &width, uint32_t &height) const;
    Texture waitAndAcquireSwapchainTexture(SDL_Window *window, uint32_t &width, uint32_t &height) const;
    CopyPass beginCopyPass() const;
    RenderPass beginRenderPass(const Texture &target, const FColour &clearColour) const;
    CommandBuffer &operator=(const CommandBuffer &) = delete;
    CommandBuffer &operator=(CommandBuffer &&rhs) noexcept;
private:
    // Internal Functions
    SDL_GPUCommandBuffer *verifyAccess(utf8_cptr_t operation) const;

    // Internal Fields
    SDL_GPUDevice *_parentDevice;
    SDL_GPUCommandBuffer *_commandBuffer;
};

//! @brief An object wrapping a window attached to a GPU swap chain.
class Swapchain
{
public:
    // Construction/Destruction
    Swapchain();
    Swapchain(SDL_GPUDevice *device, SDL_Window *window);
    Swapchain(const Swapchain &) = delete;
    Swapchain(Swapchain &&rhs) noexcept;
    ~Swapchain();

    // Accessors
    bool isBound() const;
    SDL_GPUTextureFormat getFormat() const;
    bool supportPresentMode(SDL_GPUPresentMode mode) const;
    bool supportsComposition(SDL_GPUSwapchainComposition composition) const;

    // Operations
    void release();
    Swapchain &operator=(const Swapchain &) = delete;
    Swapchain &operator=(Swapchain &&rhs) noexcept;
private:
    // Internal Fields
    SDL_GPUDevice *_device;
    SDL_Window *_window;
};

//! @brief An object used to incrementally construct the specification for a
//! texture sampler.
class SamplerBuilder
{
public:
    // Construction/Destruction
    SamplerBuilder(const Device &gpu);

    // Accessors
    const SDL_GPUSamplerCreateInfo &getCreationParameters() const;

    // Operations
    void reset();
    void setFilter(SDL_GPUFilter bothFilters);
    void setFilter(SDL_GPUFilter minFilter, SDL_GPUFilter magFilter);
    void setMipMapMode(SDL_GPUSamplerMipmapMode mode);
    void setAddressMode(SDL_GPUSamplerAddressMode mode);
    void setAddressMode(SDL_GPUSamplerAddressMode uMode, SDL_GPUSamplerAddressMode vMode,
                        SDL_GPUSamplerAddressMode wMode);
    void setLODParameters(float bias, float minLOD, float maxLOD);
    void setMaxAnisotropy(float max);
    void disableAnisotropy();
    void setComparisonOperator(SDL_GPUCompareOp op);
    void disableComparison();

    Sampler create() const;
private:
    // Internal Fields
    SDL_GPUSamplerCreateInfo _info;
    SDL_GPUDevice *_parentDevice;
};

//! @brief A wrapper for an SDL_GPUDevice resource.
class Device
{
public:
    // Construction/Destruction
    Device();
    Device(SDL_GPUDevice *resource);
    Device(const Device &rhs) = delete;
    Device(Device &&rhs) noexcept;
    ~Device();

    // Accessors
    bool isBound() const;
    string_cref_t getBackendName() const;
    SDL_GPUShaderFormat getSupportedShaderFormats() const;
    static StringCollection getAvailableBackends();
    //PropertySet getProperties() const;
    SDL_GPUShaderFormat getShaderFormats() const;

    bool supportsTextureFormat(SDL_GPUTextureFormat format, SDL_GPUTextureType type,
                               SDL_GPUTextureUsageFlags usage) const;
    bool supportsTextureSampleCount(SDL_GPUTextureFormat format,
                                    SDL_GPUSampleCount sampleCount) const;

    // Operations
    void create(SDL_GPUShaderFormat shaderFormatFlags, bool debug, utf8_cptr_t preferredBackEnd);
    bool tryCreate(SDL_GPUShaderFormat shaderFormatFlags, bool debug, utf8_cptr_t preferredBackEnd);
    TransferBuffer createTransferBuffer(SDL_GPUTransferBufferUsage usage, uint32_t size) const;
    ResourceBuffer createResourceBuffer(SDL_GPUBufferUsageFlags usage, uint32_t size) const;
    Texture createTexture(const SDL_GPUTextureCreateInfo &info) const;
    Shader createShader(const SDL_GPUShaderCreateInfo &info) const;
    Sampler createSampler(const SDL_GPUSamplerCreateInfo &info) const;
    GraphicsPipeline createGraphicsPipeline(const SDL_GPUGraphicsPipelineCreateInfo &info) const;
    void release();

    Device &operator=(SDL_GPUDevice *rhs);
    Device &operator=(const Device &rhs) = delete;
    Device &operator=(Device &&rhs) noexcept;
    Swapchain createSwapchain(SDL_Window *window) const;
    Swapchain createSwapchain(const Window &window) const;
    CommandBuffer acquireCommandBuffer() const;

    // TODO: Operations to implement:
    //SDL_CreateGPUComputePipeline
    //SDL_ReleaseGPUComputePipeline
    //SDL_CreateGPUSampler
    //SDL_GDKResumeGPU
    //SDL_GDKSuspendGPU
    //SDL_SetGPUAllowedFramesInFlight
    //SDL_SetGPUBufferName
    //SDL_SetGPUSwapchainParameters
    //SDL_SetGPUTextureName
    //SDL_WaitForGPUFences
    //SDL_WaitForGPUIdle
    //SDL_WaitForGPUSwapchain

    SDL_GPUDevice *verifyAccess(const char *operation) const;
private:
    // Internal Types

    // Internal Functions
    bool init(SDL_GPUDevice *device);

    // Internal Fields
    SDL_GPUDevice *_device;
    String _backendName;
};

}}} // namespace Ag::SDL3::GPU

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
