:: Updates and builds Google V8. Note: this must be 
:: run from a visual studio command prompt

:: Set the path to explicitly have Python2.7 & scripts
SET PATH=C:\Python27;c:\Python27\Scripts;%PATH%

:: Get V8 in READONLY mode
svn checkout http://v8.googlecode.com/svn/trunk/ v8-read-only

:: Build V8.
pushd v8-read-only
scons env="PATH:%PATH%,INCLUDE:%INCLUDE%,LIB:%LIB%" msvcrt=shared
popd
