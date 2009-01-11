===Google Test Setup===

In amd-spl, we use googletest to do unit test, please set enviroment variable 
(GOOGLETEST_ROOT) as your google test root directory.

For example:
set GOOGLETEST_ROOT = C:\Program Files\Google\gtest-1.2.1

make sure you have built the googletest and place gtest.lib and gtestd.lib at
path "$(GOOGLETEST_ROOT)\lib"
