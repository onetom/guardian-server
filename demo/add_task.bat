schtasks /create /tn guardian_server /tr "%~dp0guardian_server.exe" /sc onlogon /RL HIGHEST
