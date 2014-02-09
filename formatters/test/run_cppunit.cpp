// Blatantly plagiarized from the cppunit cookbook. The neat thing
// about this code is all you need to do is write your test class,
// put CPPUNIT_TEST_SUITE_REGISTRATION(my_class) at the bottom of
// the file and link it to this one, and all the tests thus linked
// will run! God those cppunit guys ROCK!

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

int main( int argc, char **argv)
{
  CppUnit::TextUi::TestRunner runner;
  CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
  runner.addTest( registry.makeTest() );
  bool wasSuccessful = runner.run( "", false );
  return wasSuccessful;
}
