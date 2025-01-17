#ifndef binpac_exception_h
#define binpac_exception_h

#include <inttypes.h>
#include <stdint.h>

namespace binpac
	{

class Exception
	{
public:
	Exception(const char* m = 0) : msg_("binpac exception: ")
		{
		if ( m )
			append(m);
		// abort();
		}

	void append(string m) { msg_ += m; }
	string msg() const { return msg_; }
	const char* c_msg() const { return msg_.c_str(); }

protected:
	string msg_;
	};

class ExceptionEnforceViolation : public Exception
	{
public:
	ExceptionEnforceViolation(const char* where)
		{
		append(binpac_fmt("&enforce violation : %s", where));
		}
	};

class ExceptionOutOfBound : public Exception
	{
public:
	ExceptionOutOfBound(const char* where, int len_needed, int len_given)
		{
		append(binpac_fmt("out_of_bound: %s: %d > %d", where, len_needed, len_given));
		}
	};

class ExceptionInvalidCase : public Exception
	{
public:
	ExceptionInvalidCase(const char* location, int64_t index, const char* expected)
		: location_(location), index_(index), expected_(expected)
		{
		append(binpac_fmt("invalid case: %s: %" PRIi64 " (%s)", location, index, expected));
		}

protected:
	const char* location_;
	int64_t index_;
	string expected_;
	};

class ExceptionInvalidCaseIndex : public Exception
	{
public:
	ExceptionInvalidCaseIndex(const char* location, int64_t index)
		: location_(location), index_(index)
		{
		append(binpac_fmt("invalid index for case: %s: %" PRIi64, location, index));
		}

protected:
	const char* location_;
	int64_t index_;
	};

class ExceptionInvalidOffset : public Exception
	{
public:
	ExceptionInvalidOffset(const char* location, int min_offset, int offset)
		: location_(location), min_offset_(min_offset), offset_(offset)
		{
		append(binpac_fmt("invalid offset: %s: min_offset = %d, offset = %d", location, min_offset,
		                  offset));
		}

protected:
	const char* location_;
	int min_offset_, offset_;
	};

class ExceptionStringMismatch : public Exception
	{
public:
	ExceptionStringMismatch(const char* location, const char* expected, const char* actual_data)
		{
		append(binpac_fmt("string mismatch at %s: \nexpected pattern: \"%s\"\nactual data: \"%s\"",
		                  location, expected, actual_data));
		}
	};

class ExceptionInvalidStringLength : public Exception
	{
public:
	ExceptionInvalidStringLength(const char* location, int len)
		{
		append(binpac_fmt("invalid length string: %s: %d", location, len));
		}
	};

class ExceptionFlowBufferAlloc : public Exception
	{
public:
	ExceptionFlowBufferAlloc(const char* reason)
		{
		append(binpac_fmt("flowbuffer allocation failed: %s", reason));
		}
	};

	}

#endif // binpac_exception_h
