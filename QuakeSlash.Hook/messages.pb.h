// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: messages.proto

#ifndef PROTOBUF_messages_2eproto__INCLUDED
#define PROTOBUF_messages_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

namespace pokerslashproto {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_messages_2eproto();
void protobuf_AssignDesc_messages_2eproto();
void protobuf_ShutdownFile_messages_2eproto();

class Log;
class Command;
class Message;

enum Command_CommandType {
  Command_CommandType_UNKNOWN = 0,
  Command_CommandType_BET = 1,
  Command_CommandType_CALL = 2,
  Command_CommandType_FLOP = 3,
  Command_CommandType_RAISE = 4
};
bool Command_CommandType_IsValid(int value);
const Command_CommandType Command_CommandType_CommandType_MIN = Command_CommandType_UNKNOWN;
const Command_CommandType Command_CommandType_CommandType_MAX = Command_CommandType_RAISE;
const int Command_CommandType_CommandType_ARRAYSIZE = Command_CommandType_CommandType_MAX + 1;

const ::google::protobuf::EnumDescriptor* Command_CommandType_descriptor();
inline const ::std::string& Command_CommandType_Name(Command_CommandType value) {
  return ::google::protobuf::internal::NameOfEnum(
    Command_CommandType_descriptor(), value);
}
inline bool Command_CommandType_Parse(
    const ::std::string& name, Command_CommandType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Command_CommandType>(
    Command_CommandType_descriptor(), name, value);
}
// ===================================================================

class Log : public ::google::protobuf::Message {
 public:
  Log();
  virtual ~Log();
  
  Log(const Log& from);
  
  inline Log& operator=(const Log& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Log& default_instance();
  
  void Swap(Log* other);
  
  // implements Message ----------------------------------------------
  
  Log* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Log& from);
  void MergeFrom(const Log& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required string text = 1;
  inline bool has_text() const;
  inline void clear_text();
  static const int kTextFieldNumber = 1;
  inline const ::std::string& text() const;
  inline void set_text(const ::std::string& value);
  inline void set_text(const char* value);
  inline void set_text(const char* value, size_t size);
  inline ::std::string* mutable_text();
  inline ::std::string* release_text();
  
  // @@protoc_insertion_point(class_scope:pokerslashproto.Log)
 private:
  inline void set_has_text();
  inline void clear_has_text();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* text_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_messages_2eproto();
  friend void protobuf_AssignDesc_messages_2eproto();
  friend void protobuf_ShutdownFile_messages_2eproto();
  
  void InitAsDefaultInstance();
  static Log* default_instance_;
};
// -------------------------------------------------------------------

class Command : public ::google::protobuf::Message {
 public:
  Command();
  virtual ~Command();
  
  Command(const Command& from);
  
  inline Command& operator=(const Command& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Command& default_instance();
  
  void Swap(Command* other);
  
  // implements Message ----------------------------------------------
  
  Command* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Command& from);
  void MergeFrom(const Command& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  typedef Command_CommandType CommandType;
  static const CommandType UNKNOWN = Command_CommandType_UNKNOWN;
  static const CommandType BET = Command_CommandType_BET;
  static const CommandType CALL = Command_CommandType_CALL;
  static const CommandType FLOP = Command_CommandType_FLOP;
  static const CommandType RAISE = Command_CommandType_RAISE;
  static inline bool CommandType_IsValid(int value) {
    return Command_CommandType_IsValid(value);
  }
  static const CommandType CommandType_MIN =
    Command_CommandType_CommandType_MIN;
  static const CommandType CommandType_MAX =
    Command_CommandType_CommandType_MAX;
  static const int CommandType_ARRAYSIZE =
    Command_CommandType_CommandType_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  CommandType_descriptor() {
    return Command_CommandType_descriptor();
  }
  static inline const ::std::string& CommandType_Name(CommandType value) {
    return Command_CommandType_Name(value);
  }
  static inline bool CommandType_Parse(const ::std::string& name,
      CommandType* value) {
    return Command_CommandType_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // required .pokerslashproto.Command.CommandType type = 1 [default = UNKNOWN];
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 1;
  inline ::pokerslashproto::Command_CommandType type() const;
  inline void set_type(::pokerslashproto::Command_CommandType value);
  
  // repeated string arg = 2;
  inline int arg_size() const;
  inline void clear_arg();
  static const int kArgFieldNumber = 2;
  inline const ::std::string& arg(int index) const;
  inline ::std::string* mutable_arg(int index);
  inline void set_arg(int index, const ::std::string& value);
  inline void set_arg(int index, const char* value);
  inline void set_arg(int index, const char* value, size_t size);
  inline ::std::string* add_arg();
  inline void add_arg(const ::std::string& value);
  inline void add_arg(const char* value);
  inline void add_arg(const char* value, size_t size);
  inline const ::google::protobuf::RepeatedPtrField< ::std::string>& arg() const;
  inline ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_arg();
  
  // @@protoc_insertion_point(class_scope:pokerslashproto.Command)
 private:
  inline void set_has_type();
  inline void clear_has_type();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::std::string> arg_;
  int type_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_messages_2eproto();
  friend void protobuf_AssignDesc_messages_2eproto();
  friend void protobuf_ShutdownFile_messages_2eproto();
  
  void InitAsDefaultInstance();
  static Command* default_instance_;
};
// -------------------------------------------------------------------

class Message : public ::google::protobuf::Message {
 public:
  Message();
  virtual ~Message();
  
  Message(const Message& from);
  
  inline Message& operator=(const Message& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Message& default_instance();
  
  void Swap(Message* other);
  
  // implements Message ----------------------------------------------
  
  Message* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Message& from);
  void MergeFrom(const Message& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // optional .pokerslashproto.Log log = 1;
  inline bool has_log() const;
  inline void clear_log();
  static const int kLogFieldNumber = 1;
  inline const ::pokerslashproto::Log& log() const;
  inline ::pokerslashproto::Log* mutable_log();
  inline ::pokerslashproto::Log* release_log();
  
  // optional .pokerslashproto.Command command = 2;
  inline bool has_command() const;
  inline void clear_command();
  static const int kCommandFieldNumber = 2;
  inline const ::pokerslashproto::Command& command() const;
  inline ::pokerslashproto::Command* mutable_command();
  inline ::pokerslashproto::Command* release_command();
  
  // @@protoc_insertion_point(class_scope:pokerslashproto.Message)
 private:
  inline void set_has_log();
  inline void clear_has_log();
  inline void set_has_command();
  inline void clear_has_command();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::pokerslashproto::Log* log_;
  ::pokerslashproto::Command* command_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_messages_2eproto();
  friend void protobuf_AssignDesc_messages_2eproto();
  friend void protobuf_ShutdownFile_messages_2eproto();
  
  void InitAsDefaultInstance();
  static Message* default_instance_;
};
// ===================================================================


// ===================================================================

// Log

// required string text = 1;
inline bool Log::has_text() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Log::set_has_text() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Log::clear_has_text() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Log::clear_text() {
  if (text_ != &::google::protobuf::internal::kEmptyString) {
    text_->clear();
  }
  clear_has_text();
}
inline const ::std::string& Log::text() const {
  return *text_;
}
inline void Log::set_text(const ::std::string& value) {
  set_has_text();
  if (text_ == &::google::protobuf::internal::kEmptyString) {
    text_ = new ::std::string;
  }
  text_->assign(value);
}
inline void Log::set_text(const char* value) {
  set_has_text();
  if (text_ == &::google::protobuf::internal::kEmptyString) {
    text_ = new ::std::string;
  }
  text_->assign(value);
}
inline void Log::set_text(const char* value, size_t size) {
  set_has_text();
  if (text_ == &::google::protobuf::internal::kEmptyString) {
    text_ = new ::std::string;
  }
  text_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Log::mutable_text() {
  set_has_text();
  if (text_ == &::google::protobuf::internal::kEmptyString) {
    text_ = new ::std::string;
  }
  return text_;
}
inline ::std::string* Log::release_text() {
  clear_has_text();
  if (text_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = text_;
    text_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// -------------------------------------------------------------------

// Command

// required .pokerslashproto.Command.CommandType type = 1 [default = UNKNOWN];
inline bool Command::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Command::set_has_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Command::clear_has_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Command::clear_type() {
  type_ = 0;
  clear_has_type();
}
inline ::pokerslashproto::Command_CommandType Command::type() const {
  return static_cast< ::pokerslashproto::Command_CommandType >(type_);
}
inline void Command::set_type(::pokerslashproto::Command_CommandType value) {
  GOOGLE_DCHECK(::pokerslashproto::Command_CommandType_IsValid(value));
  set_has_type();
  type_ = value;
}

// repeated string arg = 2;
inline int Command::arg_size() const {
  return arg_.size();
}
inline void Command::clear_arg() {
  arg_.Clear();
}
inline const ::std::string& Command::arg(int index) const {
  return arg_.Get(index);
}
inline ::std::string* Command::mutable_arg(int index) {
  return arg_.Mutable(index);
}
inline void Command::set_arg(int index, const ::std::string& value) {
  arg_.Mutable(index)->assign(value);
}
inline void Command::set_arg(int index, const char* value) {
  arg_.Mutable(index)->assign(value);
}
inline void Command::set_arg(int index, const char* value, size_t size) {
  arg_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Command::add_arg() {
  return arg_.Add();
}
inline void Command::add_arg(const ::std::string& value) {
  arg_.Add()->assign(value);
}
inline void Command::add_arg(const char* value) {
  arg_.Add()->assign(value);
}
inline void Command::add_arg(const char* value, size_t size) {
  arg_.Add()->assign(reinterpret_cast<const char*>(value), size);
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
Command::arg() const {
  return arg_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
Command::mutable_arg() {
  return &arg_;
}

// -------------------------------------------------------------------

// Message

// optional .pokerslashproto.Log log = 1;
inline bool Message::has_log() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Message::set_has_log() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Message::clear_has_log() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Message::clear_log() {
  if (log_ != NULL) log_->::pokerslashproto::Log::Clear();
  clear_has_log();
}
inline const ::pokerslashproto::Log& Message::log() const {
  return log_ != NULL ? *log_ : *default_instance_->log_;
}
inline ::pokerslashproto::Log* Message::mutable_log() {
  set_has_log();
  if (log_ == NULL) log_ = new ::pokerslashproto::Log;
  return log_;
}
inline ::pokerslashproto::Log* Message::release_log() {
  clear_has_log();
  ::pokerslashproto::Log* temp = log_;
  log_ = NULL;
  return temp;
}

// optional .pokerslashproto.Command command = 2;
inline bool Message::has_command() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Message::set_has_command() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Message::clear_has_command() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Message::clear_command() {
  if (command_ != NULL) command_->::pokerslashproto::Command::Clear();
  clear_has_command();
}
inline const ::pokerslashproto::Command& Message::command() const {
  return command_ != NULL ? *command_ : *default_instance_->command_;
}
inline ::pokerslashproto::Command* Message::mutable_command() {
  set_has_command();
  if (command_ == NULL) command_ = new ::pokerslashproto::Command;
  return command_;
}
inline ::pokerslashproto::Command* Message::release_command() {
  clear_has_command();
  ::pokerslashproto::Command* temp = command_;
  command_ = NULL;
  return temp;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pokerslashproto

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::pokerslashproto::Command_CommandType>() {
  return ::pokerslashproto::Command_CommandType_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_messages_2eproto__INCLUDED