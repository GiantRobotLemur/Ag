//! @file Win32Base/ComTools.cpp
//! @brief The definition of tools useful for interracting with COM.
//! @author Nick Arkell
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Core/Format.hpp"
#include "Ag/Core/VariantTypes.hpp"

#include "Ag/Win32Base/ComTools.hpp"

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// ComDomain Member Definitions
////////////////////////////////////////////////////////////////////////////////
ComDomain::ComDomain(const std::pair<HRESULT, std::string_view> *mappings, size_t count,
                     const ComDomain *parent /*= nullptr*/) :
    _parent(parent)
{
    _mappings.reserve(count);
    _mappings.appendRange(mappings, mappings + count);
    _mappings.reindex();
}

bool ComDomain::tryGetMessage(HRESULT hr, Ag::string_ref_t message) const
{
    auto pos = _mappings.find(hr);
    bool hasMapping = false;

    if (pos == _mappings.end())
    {
        if (_parent != nullptr)
        {
            hasMapping = _parent->tryGetMessage(hr, message);
        }
    }
    else
    {
        message = pos->second;
        hasMapping = true;
    }

    return hasMapping;
}

const ComDomain &ComDomain::getCoreDomain()
{
#pragma region COM Error Codes
    static const std::pair<HRESULT, std::string_view> mappings[] = {
        { E_UNEXPECTED, "Catastrophic failure" }, // 0x8000FFFF
        { E_NOTIMPL, "Not implemented" }, // 0x80004001
        { E_OUTOFMEMORY, "Ran out of memory" }, // 0x8007000E
        { E_INVALIDARG, "One or more arguments are invalid" }, // 0x80070057
        { E_NOINTERFACE, "No such interface supported" }, // 0x80004002
        { E_POINTER, "Invalid pointer" }, // 0x80004003
        { E_HANDLE, "Invalid handle" }, // 0x80070006
        { E_ABORT, "Operation aborted" }, // 0x80004004
        { E_FAIL, "Unspecified error" }, // 0x80004005
        { E_ACCESSDENIED, "General access denied error" }, // 0x80070005
        { E_PENDING, "The data necessary to complete this operation is not yet available." }, // 0x8000000A
        { E_BOUNDS, "The operation attempted to access data outside the valid range" }, // 0x8000000B
        { E_CHANGED_STATE, "A concurrent or interleaved operation changed the state of the object, invalidating this operation." }, // 0x8000000C
        { E_ILLEGAL_STATE_CHANGE, "An illegal state change was requested." }, // 0x8000000D
        { E_ILLEGAL_METHOD_CALL, "A method was called at an unexpected time." }, // 0x8000000E
        { RO_E_METADATA_NAME_NOT_FOUND, "Typename or Namespace was not found in metadata file." }, // 0x8000000F
        { RO_E_METADATA_NAME_IS_NAMESPACE, "Name is an existing namespace rather than a typename." }, // 0x80000010
        { RO_E_METADATA_INVALID_TYPE_FORMAT, "Typename has an invalid format." }, // 0x80000011
        { RO_E_INVALID_METADATA_FILE, "Metadata file is invalid or corrupted." }, // 0x80000012
        { RO_E_CLOSED, "The object has been closed." }, // 0x80000013
        { RO_E_EXCLUSIVE_WRITE, "Only one thread may access the object during a write operation." }, // 0x80000014
        { RO_E_CHANGE_NOTIFICATION_IN_PROGRESS, "Operation is prohibited during change notification." }, // 0x80000015
        { RO_E_ERROR_STRING_NOT_FOUND, "The text associated with this error code could not be found." }, // 0x80000016
        { E_STRING_NOT_NULL_TERMINATED, "String not null terminated." }, // 0x80000017
        { E_ILLEGAL_DELEGATE_ASSIGNMENT, "A delegate was assigned when not allowed." }, // 0x80000018
        { E_ASYNC_OPERATION_NOT_STARTED, "An async operation was not properly started." }, // 0x80000019
        { E_APPLICATION_EXITING, "The application is exiting and cannot service this request." }, // 0x8000001A
        { E_APPLICATION_VIEW_EXITING, "The application view is exiting and cannot service this request." }, // 0x8000001B
        { RO_E_MUST_BE_AGILE, "The object must support the IAgileObject interface." }, // 0x8000001C
        { RO_E_UNSUPPORTED_FROM_MTA, "Activating a single-threaded class from MTA is not supported." }, // 0x8000001D
        { RO_E_COMMITTED, "The object has been committed." }, // 0x8000001E
        { CO_E_INIT_TLS, "Thread local storage failure" }, // 0x80004006
        { CO_E_INIT_SHARED_ALLOCATOR, "Get shared memory allocator failure" }, // 0x80004007
        { CO_E_INIT_MEMORY_ALLOCATOR, "Get memory allocator failure" }, // 0x80004008
        { CO_E_INIT_CLASS_CACHE, "Unable to initialize class cache" }, // 0x80004009
        { CO_E_INIT_RPC_CHANNEL, "Unable to initialize RPC services" }, // 0x8000400A
        { CO_E_INIT_TLS_SET_CHANNEL_CONTROL, "Cannot set thread local storage channel control" }, // 0x8000400B
        { CO_E_INIT_TLS_CHANNEL_CONTROL, "Could not allocate thread local storage channel control" }, // 0x8000400C
        { CO_E_INIT_UNACCEPTED_USER_ALLOCATOR, "The user supplied memory allocator is unacceptable" }, // 0x8000400D
        { CO_E_INIT_SCM_MUTEX_EXISTS, "The OLE service mutex already exists" }, // 0x8000400E
        { CO_E_INIT_SCM_FILE_MAPPING_EXISTS, "The OLE service file mapping already exists" }, // 0x8000400F
        { CO_E_INIT_SCM_MAP_VIEW_OF_FILE, "Unable to map view of file for OLE service" }, // 0x80004010
        { CO_E_INIT_SCM_EXEC_FAILURE, "Failure attempting to launch OLE service" }, // 0x80004011
        { CO_E_INIT_ONLY_SINGLE_THREADED, "There was an attempt to call CoInitialize a second time while single threaded" }, // 0x80004012
        { CO_E_CANT_REMOTE, "A Remote activation was necessary but was not allowed" }, // 0x80004013
        { CO_E_BAD_SERVER_NAME, "A Remote activation was necessary but the server name provided was invalid" }, // 0x80004014
        { CO_E_WRONG_SERVER_IDENTITY, "The class is configured to run as a security id different from the caller" }, // 0x80004015
        { CO_E_OLE1DDE_DISABLED, "Use of Ole1 services requiring DDE windows is disabled" }, // 0x80004016
        { CO_E_RUNAS_SYNTAX, "A RunAs specification must be <domain name>\\<user name> or simply <user name>." }, // 0x80004017
        { CO_E_CREATEPROCESS_FAILURE, "The server process could not be started. The pathname may be incorrect." }, // 0x80004018
        { CO_E_RUNAS_CREATEPROCESS_FAILURE, "The server process could not be started as the configured identity. The pathname may be incorrect or unavailable." }, // 0x80004019
        { CO_E_RUNAS_LOGON_FAILURE, "The server process could not be started because the configured identity is incorrect. Check the user name and password." }, // 0x8000401A
        { CO_E_LAUNCH_PERMSSION_DENIED, "The client is not allowed to launch this server." }, // 0x8000401B
        { CO_E_START_SERVICE_FAILURE, "The service providing this server could not be started." }, // 0x8000401C
        { CO_E_REMOTE_COMMUNICATION_FAILURE, "This computer was unable to communicate with the computer providing the server." }, // 0x8000401D
        { CO_E_SERVER_START_TIMEOUT, "The server did not respond after being launched." }, // 0x8000401E
        { CO_E_CLSREG_INCONSISTENT, "The registration information for this server is inconsistent or incomplete." }, // 0x8000401F
        { CO_E_IIDREG_INCONSISTENT, "The registration information for this interface is inconsistent or incomplete." }, // 0x80004020
        { CO_E_NOT_SUPPORTED, "The operation attempted is not supported." }, // 0x80004021
        { CO_E_RELOAD_DLL, "A dll must be loaded." }, // 0x80004022
        { CO_E_MSI_ERROR, "A Microsoft Software Installer error was encountered." }, // 0x80004023
        { CO_E_ATTEMPT_TO_CREATE_OUTSIDE_CLIENT_CONTEXT, "The specified activation could not occur in the client context as specified." }, // 0x80004024
        { CO_E_SERVER_PAUSED, "Activations on the server are paused." }, // 0x80004025
        { CO_E_SERVER_NOT_PAUSED, "Activations on the server are not paused." }, // 0x80004026
        { CO_E_CLASS_DISABLED, "The component or application containing the component has been disabled." }, // 0x80004027
        { CO_E_CLRNOTAVAILABLE, "The common language runtime is not available" }, // 0x80004028
        { CO_E_ASYNC_WORK_REJECTED, "The thread-pool rejected the submitted asynchronous work." }, // 0x80004029
        { CO_E_SERVER_INIT_TIMEOUT, "The server started, but did not finish initializing in a timely fashion." }, // 0x8000402A
        { CO_E_NO_SECCTX_IN_ACTIVATE, "Unable to complete the call since there is no COM+ security context inside IObjectControl.Activate." }, // 0x8000402B
        { CO_E_TRACKER_CONFIG, "The provided tracker configuration is invalid" }, // 0x80004030
        { CO_E_THREADPOOL_CONFIG, "The provided thread pool configuration is invalid" }, // 0x80004031
        { CO_E_SXS_CONFIG, "The provided side-by-side configuration is invalid" }, // 0x80004032
        { CO_E_MALFORMED_SPN, "The server principal name (SPN) obtained during security negotiation is malformed." }, // 0x80004033
        { OLE_E_OLEVERB, "Invalid OLEVERB structure" }, // 0x80040000
        { OLE_E_ADVF, "Invalid advise flags" }, // 0x80040001
        { OLE_E_ENUM_NOMORE, "Can't enumerate any more, because the associated data is missing" }, // 0x80040002
        { OLE_E_ADVISENOTSUPPORTED, "This implementation doesn't take advises" }, // 0x80040003
        { OLE_E_NOCONNECTION, "There is no connection for this connection ID" }, // 0x80040004
        { OLE_E_NOTRUNNING, "Need to run the object to perform this operation" }, // 0x80040005
        { OLE_E_NOCACHE, "There is no cache to operate on" }, // 0x80040006
        { OLE_E_BLANK, "Uninitialized object" }, // 0x80040007
        { OLE_E_CLASSDIFF, "Linked object's source class has changed" }, // 0x80040008
        { OLE_E_CANT_GETMONIKER, "Not able to get the moniker of the object" }, // 0x80040009
        { OLE_E_CANT_BINDTOSOURCE, "Not able to bind to the source" }, // 0x8004000A
        { OLE_E_STATIC, "Object is static; operation not allowed" }, // 0x8004000B
        { OLE_E_PROMPTSAVECANCELLED, "User canceled out of save dialog" }, // 0x8004000C
        { OLE_E_INVALIDRECT, "Invalid rectangle" }, // 0x8004000D
        { OLE_E_WRONGCOMPOBJ, "compobj.dll is too old for the ole2.dll initialized" }, // 0x8004000E
        { OLE_E_INVALIDHWND, "Invalid window handle" }, // 0x8004000F
        { OLE_E_NOT_INPLACEACTIVE, "Object is not in any of the inplace active states" }, // 0x80040010
        { OLE_E_CANTCONVERT, "Not able to convert object" }, // 0x80040011
        { OLE_E_NOSTORAGE, "Not able to perform the operation because object is not given storage yet" }, // 0x80040012
        { DV_E_FORMATETC, "Invalid FORMATETC structure" }, // 0x80040064
        { DV_E_DVTARGETDEVICE, "Invalid DVTARGETDEVICE structure" }, // 0x80040065
        { DV_E_STGMEDIUM, "Invalid STDGMEDIUM structure" }, // 0x80040066
        { DV_E_STATDATA, "Invalid STATDATA structure" }, // 0x80040067
        { DV_E_LINDEX, "Invalid lindex" }, // 0x80040068
        { DV_E_TYMED, "Invalid tymed" }, // 0x80040069
        { DV_E_CLIPFORMAT, "Invalid clipboard format" }, // 0x8004006A
        { DV_E_DVASPECT, "Invalid aspect(s)" }, // 0x8004006B
        { DV_E_DVTARGETDEVICE_SIZE, "tdSize parameter of the DVTARGETDEVICE structure is invalid" }, // 0x8004006C
        { DV_E_NOIVIEWOBJECT, "Object doesn't support IViewObject interface" }, // 0x8004006D
        { DRAGDROP_E_NOTREGISTERED, "Trying to revoke a drop target that has not been registered" }, // 0x80040100
        { DRAGDROP_E_ALREADYREGISTERED, "This window has already been registered as a drop target" }, // 0x80040101
        { DRAGDROP_E_INVALIDHWND, "Invalid window handle" }, // 0x80040102
        { CLASS_E_NOAGGREGATION, "Class does not support aggregation (or class object is remote)" }, // 0x80040110
        { CLASS_E_CLASSNOTAVAILABLE, "ClassFactory cannot supply requested class" }, // 0x80040111
        { CLASS_E_NOTLICENSED, "Class is not licensed for use" }, // 0x80040112
        { VIEW_E_DRAW, "Error drawing view" }, // 0x80040140
        { REGDB_E_READREGDB, "Could not read key from registry" }, // 0x80040150
        { REGDB_E_WRITEREGDB, "Could not write key to registry" }, // 0x80040151
        { REGDB_E_KEYMISSING, "Could not find the key in the registry" }, // 0x80040152
        { REGDB_E_INVALIDVALUE, "Invalid value for registry" }, // 0x80040153
        { REGDB_E_CLASSNOTREG, "Class not registered" }, // 0x80040154
        { REGDB_E_IIDNOTREG, "Interface not registered" }, // 0x80040155
        { REGDB_E_BADTHREADINGMODEL, "Threading model entry is not valid" }, // 0x80040156
        { CAT_E_CATIDNOEXIST, "CATID does not exist" }, // 0x80040160
        { CAT_E_NODESCRIPTION, "Description not found" }, // 0x80040161
        { CS_E_PACKAGE_NOTFOUND, "No package in the software installation data in the Active Directory meets this criteria." }, // 0x80040164
        { CS_E_NOT_DELETABLE, "Deleting this will break the referential integrity of the software installation data in the Active Directory." }, // 0x80040165
        { CS_E_CLASS_NOTFOUND, "The CLSID was not found in the software installation data in the Active Directory." }, // 0x80040166
        { CS_E_INVALID_VERSION, "The software installation data in the Active Directory is corrupt." }, // 0x80040167
        { CS_E_NO_CLASSSTORE, "There is no software installation data in the Active Directory." }, // 0x80040168
        { CS_E_OBJECT_NOTFOUND, "There is no software installation data object in the Active Directory." }, // 0x80040169
        { CS_E_OBJECT_ALREADY_EXISTS, "The software installation data object in the Active Directory already exists." }, // 0x8004016A
        { CS_E_INVALID_PATH, "The path to the software installation data in the Active Directory is not correct." }, // 0x8004016B
        { CS_E_NETWORK_ERROR, "A network error interrupted the operation." }, // 0x8004016C
        { CS_E_ADMIN_LIMIT_EXCEEDED, "The size of this object exceeds the maximum size set by the Administrator." }, // 0x8004016D
        { CS_E_SCHEMA_MISMATCH, "The schema for the software installation data in the Active Directory does not match the required schema." }, // 0x8004016E
        { CS_E_INTERNAL_ERROR, "An error occurred in the software installation data in the Active Directory." }, // 0x8004016F
        { CACHE_E_NOCACHE_UPDATED, "Cache not updated" }, // 0x80040170
        { OLEOBJ_E_NOVERBS, "No verbs for OLE object" }, // 0x80040180
        { OLEOBJ_E_INVALIDVERB, "Invalid verb for OLE object" }, // 0x80040181
        { INPLACE_E_NOTUNDOABLE, "Undo is not available" }, // 0x800401A0
        { INPLACE_E_NOTOOLSPACE, "Space for tools is not available" }, // 0x800401A1
        { CONVERT10_E_OLESTREAM_GET, "OLESTREAM Get method failed" }, // 0x800401C0
        { CONVERT10_E_OLESTREAM_PUT, "OLESTREAM Put method failed" }, // 0x800401C1
        { CONVERT10_E_OLESTREAM_FMT, "Contents of the OLESTREAM not in correct format" }, // 0x800401C2
        { CONVERT10_E_OLESTREAM_BITMAP_TO_DIB, "There was an error in a Windows GDI call while converting the bitmap to a DIB" }, // 0x800401C3
        { CONVERT10_E_STG_FMT, "Contents of the IStorage not in correct format" }, // 0x800401C4
        { CONVERT10_E_STG_NO_STD_STREAM, "Contents of IStorage is missing one of the standard streams" }, // 0x800401C5
        { CONVERT10_E_STG_DIB_TO_BITMAP, "There was an error in a Windows GDI call while converting the DIB to a bitmap." }, // 0x800401C6
        { CLIPBRD_E_CANT_OPEN, "OpenClipboard Failed" }, // 0x800401D0
        { CLIPBRD_E_CANT_EMPTY, "EmptyClipboard Failed" }, // 0x800401D1
        { CLIPBRD_E_CANT_SET, "SetClipboard Failed" }, // 0x800401D2
        { CLIPBRD_E_BAD_DATA, "Data on clipboard is invalid" }, // 0x800401D3
        { CLIPBRD_E_CANT_CLOSE, "CloseClipboard Failed" }, // 0x800401D4
        { MK_E_CONNECTMANUALLY, "Moniker needs to be connected manually" }, // 0x800401E0
        { MK_E_EXCEEDEDDEADLINE, "Operation exceeded deadline" }, // 0x800401E1
        { MK_E_NEEDGENERIC, "Moniker needs to be generic" }, // 0x800401E2
        { MK_E_UNAVAILABLE, "Operation unavailable" }, // 0x800401E3
        { MK_E_SYNTAX, "Invalid syntax" }, // 0x800401E4
        { MK_E_NOOBJECT, "No object for moniker" }, // 0x800401E5
        { MK_E_INVALIDEXTENSION, "Bad extension for file" }, // 0x800401E6
        { MK_E_INTERMEDIATEINTERFACENOTSUPPORTED, "Intermediate operation failed" }, // 0x800401E7
        { MK_E_NOTBINDABLE, "Moniker is not bindable" }, // 0x800401E8
        { MK_E_NOTBOUND, "Moniker is not bound" }, // 0x800401E9
        { MK_E_CANTOPENFILE, "Moniker cannot open file" }, // 0x800401EA
        { MK_E_MUSTBOTHERUSER, "User input required for operation to succeed" }, // 0x800401EB
        { MK_E_NOINVERSE, "Moniker class has no inverse" }, // 0x800401EC
        { MK_E_NOSTORAGE, "Moniker does not refer to storage" }, // 0x800401ED
        { MK_E_NOPREFIX, "No common prefix" }, // 0x800401EE
        { MK_E_ENUMERATION_FAILED, "Moniker could not be enumerated" }, // 0x800401EF
        { CO_E_NOTINITIALIZED, "CoInitialize has not been called." }, // 0x800401F0
        { CO_E_ALREADYINITIALIZED, "CoInitialize has already been called." }, // 0x800401F1
        { CO_E_CANTDETERMINECLASS, "Class of object cannot be determined" }, // 0x800401F2
        { CO_E_CLASSSTRING, "Invalid class string" }, // 0x800401F3
        { CO_E_IIDSTRING, "Invalid interface string" }, // 0x800401F4
        { CO_E_APPNOTFOUND, "Application not found" }, // 0x800401F5
        { CO_E_APPSINGLEUSE, "Application cannot be run more than once" }, // 0x800401F6
        { CO_E_ERRORINAPP, "Some error in application program" }, // 0x800401F7
        { CO_E_DLLNOTFOUND, "DLL for class not found" }, // 0x800401F8
        { CO_E_ERRORINDLL, "Error in the DLL" }, // 0x800401F9
        { CO_E_WRONGOSFORAPP, "Wrong operating system or operating system version for the application" }, // 0x800401FA
        { CO_E_OBJNOTREG, "Object is not registered" }, // 0x800401FB
        { CO_E_OBJISREG, "Object is already registered" }, // 0x800401FC
        { CO_E_OBJNOTCONNECTED, "Object is not connected to server" }, // 0x800401FD
        { CO_E_APPDIDNTREG, "Application was launched but it didn't register a class factory" }, // 0x800401FE
        { CO_E_RELEASED, "Object has been released" }, // 0x800401FF
        { EVENT_S_SOME_SUBSCRIBERS_FAILED, "An event was able to invoke some but not all of the subscribers" }, // 0x00040200
        { EVENT_E_ALL_SUBSCRIBERS_FAILED, "An event was unable to invoke any of the subscribers" }, // 0x80040201
        { EVENT_S_NOSUBSCRIBERS, "An event was delivered but there were no subscribers" }, // 0x00040202
        { EVENT_E_QUERYSYNTAX, "A syntax error occurred trying to evaluate a query string" }, // 0x80040203
        { EVENT_E_QUERYFIELD, "An invalid field name was used in a query string" }, // 0x80040204
        { EVENT_E_INTERNALEXCEPTION, "An unexpected exception was raised" }, // 0x80040205
        { EVENT_E_INTERNALERROR, "An unexpected internal error was detected" }, // 0x80040206
        { EVENT_E_INVALID_PER_USER_SID, "The owner SID on a per-user subscription doesn't exist" }, // 0x80040207
        { EVENT_E_USER_EXCEPTION, "A user-supplied component or subscriber raised an exception" }, // 0x80040208
        { EVENT_E_TOO_MANY_METHODS, "An interface has too many methods to fire events from" }, // 0x80040209
        { EVENT_E_MISSING_EVENTCLASS, "A subscription cannot be stored unless its event class already exists" }, // 0x8004020A
        { EVENT_E_NOT_ALL_REMOVED, "Not all the objects requested could be removed" }, // 0x8004020B
        { EVENT_E_COMPLUS_NOT_INSTALLED, "COM+ is required for this operation, but is not installed" }, // 0x8004020C
        { EVENT_E_CANT_MODIFY_OR_DELETE_UNCONFIGURED_OBJECT, "Cannot modify or delete an object that was not added using the COM+ Admin SDK" }, // 0x8004020D
        { EVENT_E_CANT_MODIFY_OR_DELETE_CONFIGURED_OBJECT, "Cannot modify or delete an object that was added using the COM+ Admin SDK" }, // 0x8004020E
        { EVENT_E_INVALID_EVENT_CLASS_PARTITION, "The event class for this subscription is in an invalid partition" }, // 0x8004020F
        { EVENT_E_PER_USER_SID_NOT_LOGGED_ON, "The owner of the PerUser subscription is not logged on to the system specified" }, // 0x80040210
    };
#pragma endregion

    static const ComDomain instance(mappings, std::size(mappings), nullptr);

    return instance;
}

////////////////////////////////////////////////////////////////////////////////
// GuidDomain Member Definitions
////////////////////////////////////////////////////////////////////////////////
GuidDomain::GuidDomain(const std::pair<GUID, std::string_view> *mappings, size_t count,
                       const GuidDomain *parent /*= nullptr*/) :
    _parent(parent)
{
    _mappings.reserve(count);

    for (size_t i = 0; i < count; ++i)
    {
        _mappings.push_back(mappings[i].first, mappings[i].second);
    }

    _mappings.reindex();
}

bool GuidDomain::tryGetDisplay(REFIID id, Ag::string_ref_t message) const
{
    auto pos = _mappings.find(id);
    bool hasMapping = false;

    if (pos == _mappings.end())
    {
        if (_parent != nullptr)
        {
            hasMapping = _parent->tryGetDisplay(id, message);
        }
    }
    else
    {
        message = pos->second;
        hasMapping = true;
    }

    return hasMapping;
}

const GuidDomain &GuidDomain::getCoreDomain()
{
#define ITEM(x) { __uuidof(x), # x }

    static const std::pair<GUID, std::string_view> mappings[] = {
        ITEM(IUnknown),
        ITEM(IDispatch),
    };
#undef ITEM

    static const GuidDomain core(mappings, std::size(mappings), nullptr);

    return core;
}

bool GuidDomain::GuidLess::operator()(const GUID &lhs, const GUID &rhs) const
{
    auto lhsId = reinterpret_cast<const uint64_t *>(&lhs);
    auto rhsId = reinterpret_cast<const uint64_t *>(&rhs);

    return (lhsId[1] == rhsId[1]) ? (lhsId[0] < rhsId[0]) : (lhsId[1] < rhsId[1]);
}


////////////////////////////////////////////////////////////////////////////////
// ComException Member Definitions
////////////////////////////////////////////////////////////////////////////////
ComException::ComException(const std::string_view &fnName, HRESULT hr,
                           const ComDomain &domain, IUnknown */* obj = nullptr*/)
{
    Ag::String message, detail;

    if (domain.tryGetMessage(hr, message))
    {
        detail = Ag::String::format("{0}: {1}",
                                    { fnName, message });
    }
    else
    {
        detail = Ag::String::format("COM function {0} produced an unexpected HRESULT: 0x{1:X8}.",
                                    { fnName, hr });
    }

    initialise("ComException", "A COM function returned an unexpected error code.",
                detail.toUtf8View(), static_cast<uintptr_t>(hr));
}


////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Performs a less-than comparison between GUIDs.
bool guidLessThan(REFIID lhs, REFIID rhs)
{
    auto lhsId = reinterpret_cast<const uint64_t *>(&lhs);
    auto rhsId = reinterpret_cast<const uint64_t *>(&rhs);

    return (lhsId[1] == rhsId[1]) ? (lhsId[0] < rhsId[0]) : (lhsId[1] < rhsId[1]);
}

//! @brief Perform a comparison between GUIDs.
//! @retval &lt;0 If lhsId has a lower value than rhsId.
//! @retval 0 If lhsId is equal to rhsId.
//! @retval &gt;0 If lhsId has a greater value than rhsId.
int guidCompare(REFIID lhs, REFIID rhs)
{
    auto lhsId = reinterpret_cast<const uint64_t *>(&lhs);
    auto rhsId = reinterpret_cast<const uint64_t *>(&rhs);

    int diff = 0;
    if (lhsId[1] == rhsId[1])
    {
        if (lhsId[0] != rhsId[0])
        {
            diff = (lhsId[0] < rhsId[0]) ? -1 : 1;
        }
    }
    else
    {
        diff = (lhsId[1] < rhsId[1]) ? -1 : 1;
    }

    return diff;
}

//! @brief Formats a GUID into a string.
//! @param[in] buffer The buffer to append to.
//! @param[in] iid The GUID to format.
void appendGuid(std::string &buffer, REFIID iid)
{
    Ag::appendFormat(LocaleInfo::getNeutral(),
                     "{{ {0:X8}-{1:X4}-{2:X4}-{3:X2}{4:X2}{5:X2}{6:X2}{7:X2}{8:X2} }",
                     buffer, { static_cast<uint32_t>(iid.Data1), iid.Data2, iid.Data3,
                     iid.Data4[0], iid.Data4[1], iid.Data4[2], iid.Data4[3],
                     iid.Data4[4], iid.Data4[5], iid.Data4[6], iid.Data4[7] });
}

//! @brief Attempts to translate a GUID to a useful display value.
//! @param[in] domain The domain used to look up the GUID.
//! @param[in] iid The GUID to look up.
//! @return A string giving a symbolic value or a formatted numeric value
//! of @p iid.
Ag::String iidToString(const GuidDomain &domain, REFIID iid)
{
    Ag::String text;

    if (domain.tryGetDisplay(iid, text) == false)
    {
        std::string buffer;
        buffer.reserve(40);

        appendGuid(buffer, iid);

        text = buffer;
    }

    return text;
}

}} // namespace Ag::Win32
////////////////////////////////////////////////////////////////////////////////
