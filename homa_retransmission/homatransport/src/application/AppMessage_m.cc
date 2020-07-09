//
// Generated file, do not edit! Created by nedtool 4.6 from application/AppMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "AppMessage_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

Register_Class(AppMessage);

AppMessage::AppMessage(const char *name, int kind) : ::cPacket(name,kind)
{
    this->msgCreationTime_var = 0;
    this->transportSchedDelay_var = 0;
    this->transportSchedPreemptionLag_var = 0;
    this->msgBytesOnWire_var = 0;
}

AppMessage::AppMessage(const AppMessage& other) : ::cPacket(other)
{
    copy(other);
}

AppMessage::~AppMessage()
{
}

AppMessage& AppMessage::operator=(const AppMessage& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void AppMessage::copy(const AppMessage& other)
{
    this->destAddr_var = other.destAddr_var;
    this->srcAddr_var = other.srcAddr_var;
    this->msgCreationTime_var = other.msgCreationTime_var;
    this->transportSchedDelay_var = other.transportSchedDelay_var;
    this->transportSchedPreemptionLag_var = other.transportSchedPreemptionLag_var;
    this->msgBytesOnWire_var = other.msgBytesOnWire_var;
}

void AppMessage::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->destAddr_var);
    doPacking(b,this->srcAddr_var);
    doPacking(b,this->msgCreationTime_var);
    doPacking(b,this->transportSchedDelay_var);
    doPacking(b,this->transportSchedPreemptionLag_var);
    doPacking(b,this->msgBytesOnWire_var);
}

void AppMessage::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->destAddr_var);
    doUnpacking(b,this->srcAddr_var);
    doUnpacking(b,this->msgCreationTime_var);
    doUnpacking(b,this->transportSchedDelay_var);
    doUnpacking(b,this->transportSchedPreemptionLag_var);
    doUnpacking(b,this->msgBytesOnWire_var);
}

inet::L3Address& AppMessage::getDestAddr()
{
    return destAddr_var;
}

void AppMessage::setDestAddr(const inet::L3Address& destAddr)
{
    this->destAddr_var = destAddr;
}

inet::L3Address& AppMessage::getSrcAddr()
{
    return srcAddr_var;
}

void AppMessage::setSrcAddr(const inet::L3Address& srcAddr)
{
    this->srcAddr_var = srcAddr;
}

simtime_t AppMessage::getMsgCreationTime() const
{
    return msgCreationTime_var;
}

void AppMessage::setMsgCreationTime(simtime_t msgCreationTime)
{
    this->msgCreationTime_var = msgCreationTime;
}

simtime_t AppMessage::getTransportSchedDelay() const
{
    return transportSchedDelay_var;
}

void AppMessage::setTransportSchedDelay(simtime_t transportSchedDelay)
{
    this->transportSchedDelay_var = transportSchedDelay;
}

simtime_t AppMessage::getTransportSchedPreemptionLag() const
{
    return transportSchedPreemptionLag_var;
}

void AppMessage::setTransportSchedPreemptionLag(simtime_t transportSchedPreemptionLag)
{
    this->transportSchedPreemptionLag_var = transportSchedPreemptionLag;
}

long AppMessage::getMsgBytesOnWire() const
{
    return msgBytesOnWire_var;
}

void AppMessage::setMsgBytesOnWire(long msgBytesOnWire)
{
    this->msgBytesOnWire_var = msgBytesOnWire;
}

class AppMessageDescriptor : public cClassDescriptor
{
  public:
    AppMessageDescriptor();
    virtual ~AppMessageDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(AppMessageDescriptor);

AppMessageDescriptor::AppMessageDescriptor() : cClassDescriptor("AppMessage", "cPacket")
{
}

AppMessageDescriptor::~AppMessageDescriptor()
{
}

bool AppMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<AppMessage *>(obj)!=NULL;
}

const char *AppMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int AppMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount(object) : 6;
}

unsigned int AppMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<6) ? fieldTypeFlags[field] : 0;
}

const char *AppMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "destAddr",
        "srcAddr",
        "msgCreationTime",
        "transportSchedDelay",
        "transportSchedPreemptionLag",
        "msgBytesOnWire",
    };
    return (field>=0 && field<6) ? fieldNames[field] : NULL;
}

int AppMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destAddr")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcAddr")==0) return base+1;
    if (fieldName[0]=='m' && strcmp(fieldName, "msgCreationTime")==0) return base+2;
    if (fieldName[0]=='t' && strcmp(fieldName, "transportSchedDelay")==0) return base+3;
    if (fieldName[0]=='t' && strcmp(fieldName, "transportSchedPreemptionLag")==0) return base+4;
    if (fieldName[0]=='m' && strcmp(fieldName, "msgBytesOnWire")==0) return base+5;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *AppMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",
        "inet::L3Address",
        "simtime_t",
        "simtime_t",
        "simtime_t",
        "long",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : NULL;
}

const char *AppMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int AppMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    AppMessage *pp = (AppMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string AppMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    AppMessage *pp = (AppMessage *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getDestAddr(); return out.str();}
        case 1: {std::stringstream out; out << pp->getSrcAddr(); return out.str();}
        case 2: return double2string(pp->getMsgCreationTime());
        case 3: return double2string(pp->getTransportSchedDelay());
        case 4: return double2string(pp->getTransportSchedPreemptionLag());
        case 5: return long2string(pp->getMsgBytesOnWire());
        default: return "";
    }
}

bool AppMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    AppMessage *pp = (AppMessage *)object; (void)pp;
    switch (field) {
        case 2: pp->setMsgCreationTime(string2double(value)); return true;
        case 3: pp->setTransportSchedDelay(string2double(value)); return true;
        case 4: pp->setTransportSchedPreemptionLag(string2double(value)); return true;
        case 5: pp->setMsgBytesOnWire(string2long(value)); return true;
        default: return false;
    }
}

const char *AppMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return opp_typename(typeid(inet::L3Address));
        case 1: return opp_typename(typeid(inet::L3Address));
        default: return NULL;
    };
}

void *AppMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    AppMessage *pp = (AppMessage *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getDestAddr()); break;
        case 1: return (void *)(&pp->getSrcAddr()); break;
        default: return NULL;
    }
}


