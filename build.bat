call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\bin\vcvars32.bat"
msbuild.exe /p:Configuration=Release guardian_server.sln
copy Bin\Release\guardian_server.exe Demo