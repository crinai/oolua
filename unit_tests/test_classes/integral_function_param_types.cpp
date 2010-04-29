
#	include "oolua.h"
#	include "common_cppunit_headers.h"
#	include "gmock/gmock.h"

namespace
{
	class Int_params
	{
	public:
		virtual ~Int_params(){}
		virtual void int_(int i) = 0;
		virtual void int_ref(int &) = 0;
		virtual void int_ptr(int *) = 0;
		virtual void int_const(int const i) = 0;
		virtual void int_const_ref(int const&) = 0;
		virtual void int_const_ptr(int const* i) = 0;
		virtual void int_const_ptr_const(int const * const) = 0;
		virtual void bool_(bool b) = 0;
	};

	class MockInt : public Int_params 
	{
	public:
		MOCK_METHOD1(int_,void (int) );
		MOCK_METHOD1(int_ref,void (int&) );
		MOCK_METHOD1(int_ptr,void (int*) );
		MOCK_METHOD1(int_const,void (int const ) );
		MOCK_METHOD1(int_const_ref,void (int const&) );
		MOCK_METHOD1(int_const_ptr,void (int const*) );
		MOCK_METHOD1(int_const_ptr_const,void (int const * const) );
		MOCK_METHOD1(bool_,void (bool) );
	};
	
	int int_set_value =1;
	bool bool_set_value= true;

}

OOLUA_CLASS_NO_BASES(Int_params)
	OOLUA_TYPEDEFS Abstract OOLUA_END_TYPES
	OOLUA_MEM_FUNC_1(void, int_,int)
	OOLUA_MEM_FUNC_1(void, int_ref,int& )
	OOLUA_MEM_FUNC_1(void, int_ptr,int* )
	OOLUA_MEM_FUNC_1(void, int_const,int const)
	OOLUA_MEM_FUNC_1(void, int_const_ref,int const& )
	OOLUA_MEM_FUNC_1(void, int_const_ptr,int const*  )
	OOLUA_MEM_FUNC_1(void, int_const_ptr_const,int const * const )
	OOLUA_MEM_FUNC_1(void, bool_,bool)
OOLUA_CLASS_END

EXPORT_OOLUA_FUNCTIONS_8_NON_CONST(Int_params
								   ,int_
								   ,int_ref
								   ,int_ptr
								   ,int_const
								   ,int_const_ref
								   ,int_const_ptr
								   ,int_const_ptr_const
								   ,bool_)
								
EXPORT_OOLUA_FUNCTIONS_0_CONST(Int_params)

struct IntParamHelper
{
	IntParamHelper()
	:mock()
	,mockBase(&mock)
	{}
	MockInt mock;
	Int_params* mockBase;
};



class Integral_params : public CppUnit::TestFixture 
{
	CPPUNIT_TEST_SUITE(Integral_params);
	CPPUNIT_TEST(int_intParam_calledOnceWithCorrectParam);
	CPPUNIT_TEST(int_intRefParam_calledOnceWithCorrectParam);
	CPPUNIT_TEST(int_intPtrParam_calledOnceWithCorrectParam);
	CPPUNIT_TEST(int_intConstParam_calledOnceWithCorrectParam);
	CPPUNIT_TEST(int_intConstRefParam_calledOnceWithCorrectParam);
	CPPUNIT_TEST(int_intConstPtrParam_calledOnceWithCorrectParam);
	CPPUNIT_TEST(int_intConstPtrConstParam_calledOnceWithCorrectParam);
	CPPUNIT_TEST(int_boolParam_calledOnceWithCorrectParam);
	CPPUNIT_TEST_SUITE_END();
	
	OOLUA::Script* m_lua;
	IntParamHelper* m_helper;
	//Generates a Lua function that when called and passed an class instance and param
	//will call the method (func_name) on the instance.
	//returns the Lua function name which is generated.
	std::string generate_and_run_chunk_for_the_function_named(std::string const& func_name)
	{
		std::string lua_func_name("func");
		std::string chunk ( lua_func_name + std::string(" = function(obj,param)\n")
						   +std::string("obj:") + func_name + std::string("(param)\n")
						   +std::string("end\n"));
		
		m_lua->run_chunk(chunk);
		return lua_func_name;
	}
	void generate_run_and_call(std::string const& func_name)
	{
		std::string func = generate_and_run_chunk_for_the_function_named(func_name);
		m_lua->call(func,m_helper->mockBase,int_set_value);
	}
public:
	void setUp()
	{
		m_lua = new OOLUA::Script;
		m_lua->register_class<Int_params>();
		m_helper = new IntParamHelper;
	}
	void tearDown()
	{
		delete m_lua;
		delete m_helper;
	}
	void int_intParam_calledOnceWithCorrectParam()
	{
		EXPECT_CALL(m_helper->mock,
					int_( ::testing::Eq(int_set_value) ) )
					.Times(1);
		generate_run_and_call("int_");
	}
	void int_intRefParam_calledOnceWithCorrectParam()
	{
		EXPECT_CALL(m_helper->mock,
					int_ref( ::testing::Eq(int_set_value) ) )
					.Times(1);
		generate_run_and_call("int_ref");
	}
	void int_intPtrParam_calledOnceWithCorrectParam()
	{
		EXPECT_CALL(m_helper->mock,
					int_ptr( ::testing::Pointee(int_set_value) ) )
					.Times(1);
		generate_run_and_call("int_ptr");
	}
	void int_intConstParam_calledOnceWithCorrectParam()
	{
		EXPECT_CALL(m_helper->mock,
					int_const( ::testing::Eq(int_set_value) ) )
					.Times(1);
		generate_run_and_call("int_const");
	}
	void int_intConstRefParam_calledOnceWithCorrectParam()
	{
		EXPECT_CALL(m_helper->mock,
					int_const_ref( ::testing::Eq(int_set_value) ) )
					.Times(1);
		generate_run_and_call("int_const_ref");
	}
	
	void int_intConstPtrParam_calledOnceWithCorrectParam()
	{
		EXPECT_CALL(m_helper->mock,
					int_const_ptr( ::testing::Pointee(int_set_value ) ) )
					.Times(1);
		generate_run_and_call("int_const_ptr");
	}
	
	void int_intConstPtrConstParam_calledOnceWithCorrectParam()
	{
		EXPECT_CALL(m_helper->mock,
					int_const_ptr_const( ::testing::Pointee(int_set_value ) ) )
					.Times(1);
		generate_run_and_call("int_const_ptr_const");
	}
	void int_boolParam_calledOnceWithCorrectParam()
	{
		EXPECT_CALL(m_helper->mock,
					bool_( ::testing::Eq(bool_set_value ) ) )
		.Times(1);
		std::string func = generate_and_run_chunk_for_the_function_named("bool_");
		m_lua->call(func,m_helper->mockBase,bool_set_value);
	}
};
CPPUNIT_TEST_SUITE_REGISTRATION(Integral_params);
