
# Defines:-
#
# POCO_VERSION_H
# POCO_INCLUDE_DIR
# POCO_LIBS_DIR
# POCO_LIBS
#

IF(NOT EXISTS "/usr/local/include/Poco/Version.h")
    MESSAGE(FATAL_ERROR "Failed to find /usr/local/include/Poco/Version.h")
ELSE()
	MESSAGE(STATUS "Poco found")
	SET(POCO_FOUND 1)
	SET(POCO_VERSION_H "/usr/local/include/Poco/Version.h")
	SET(POCO_INCLUDE_DIR "/usr/local/include")
	SET(POCO_LIBS_DIR "/usr/local/lib")
	SET(POCO_LIBS
		/usr/local/lib/libPocoCrypto.so
		/usr/local/lib/libPocoData.so
		/usr/local/lib/libPocoDataMySQL.so
		/usr/local/lib/libPocoDataSQLite.so
		/usr/local/lib/libPocoEncodings.so
		/usr/local/lib/libPocoFoundation.so
		/usr/local/lib/libPocoJSON.so
		/usr/local/lib/libPocoMongoDB.so
		/usr/local/lib/libPocoNet.so
		/usr/local/lib/libPocoNetSSL.so
		/usr/local/lib/libPocoRedis.so
		/usr/local/lib/libPocoUtil.so
		/usr/local/lib/libPocoXML.so
		/usr/local/lib/libPocoZip.so
	)
ENDIF()


