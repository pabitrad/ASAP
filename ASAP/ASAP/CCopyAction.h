#pragma once

#include "CCopyFilter.h"
#include "CDirectoryAction.h"
#include "OutputWriter.h"
#include "CVSSCopyException.h"

class CCopyAction : public CDirectoryAction
{
private: 
    LONGLONG _byteCount; 
    LPCTSTR _destination; 
    int _directoryCount; 
    int _fileCount; 
    vector<CCopyFilter*> _filters; 
    int _skipCount; 
    bool _skipDenied; 
    LPCTSTR _source; 

public: 
    CCopyAction::CCopyAction(LPCTSTR source, LPCTSTR destination, bool skipDenied, vector<CCopyFilter*> filters) : _filters(filters)
    {
        _source = source; 
        _destination = destination; 
        _skipDenied = skipDenied; 
        _fileCount = 0; 
        _directoryCount = 0; 
        _skipCount = 0; 
        _byteCount = 0; 
    }

    LONGLONG get_ByteCount(void)
    {
        return _byteCount; 
    }

    int get_DirectoryCount(void)
    {
        return _directoryCount; 
    }

    int get_FileCount(void)
    {
        return _fileCount; 
    }

    int get_SkipCount(void)
    {
        return _skipCount; 
    }

    void VisitDirectoryFinal(LPCTSTR path)
    {
        CString message; 
        message.AppendFormat(TEXT("Copied directory %s"), path); 
        OutputWriter::WriteLine(message, VERBOSITY_THRESHOLD_NORMAL); 
        ++_directoryCount; 
    }

    void VisitDirectoryInitial(LPCTSTR path)
    {
        CString destDir;
        Utilities::CombinePath(_destination, path, destDir);
		Utilities::CreateDirectory(destDir);
		CString message; 
		message.AppendFormat(TEXT("Created directory %s"), destDir); 
		OutputWriter::WriteLine(message, VERBOSITY_THRESHOLD_IF_VERBOSE); 
    }

	void VisitFile(LPCTSTR path) 
    {
        CString sourceFile;
        Utilities::CombinePath(_source, path, sourceFile);

        CString destinationFile; 
        Utilities::CombinePath(_destination, path, destinationFile);
        Utilities::FixLongFilenames(destinationFile); 
        if (IsFileMatch(sourceFile))
        {
            BOOL worked = ::CopyFile(sourceFile, destinationFile, false);
            if (!worked)
            {
                DWORD error = ::GetLastError();

                if ((error == 5 || error == 32) && _skipDenied)
                {
                    CString message; 
                    message.Format(TEXT("Error %d accessing file %s. Skipping."), error, sourceFile); 
                    OutputWriter::WriteLine(message, VERBOSITY_THRESHOLD_NORMAL); 
                    ++_skipCount; 
                }
                else
                {
                    CString errorMessage; 
                    Utilities::FormatErrorMessage(error, errorMessage); 
                    CString message; 
                    message.AppendFormat(TEXT("Copy of file failed with error %s on file %s"), 
                        errorMessage, sourceFile); 
                    throw new CVSSCopyException(message);
                }
            }
            else
            {
                CString message; 
                message.AppendFormat(TEXT("Copied file %s to %s"), sourceFile, destinationFile); 
                OutputWriter::WriteLine(message, VERBOSITY_THRESHOLD_IF_VERBOSE); 
                ++_fileCount; 

                try
                {
                    _byteCount += Utilities::GetFileSize(sourceFile); 
                }
                catch (CVSSCopyException* x)
                {
                    CString message; 
                    message.AppendFormat(TEXT("Unable to calculate size of file. Size calculations may be incorrect. Message was: %s"), 
                        x->get_Message()); 
                    OutputWriter::WriteLine(message, VERBOSITY_THRESHOLD_UNLESS_SILENT); 
                    delete x; 
                }
            }
        }
        else
        {
            CString message;
            message.AppendFormat(TEXT("Skipping file %s because it doesn't meet filter criteria."), path); 
            OutputWriter::WriteLine(message); 
            ++_skipCount; 
        }

    }

private:
    bool IsFileMatch(CString& file)
    {
        for (unsigned int iFilter = 0; iFilter < _filters.size(); ++iFilter)
        {
            if (!_filters[iFilter]->IsFileMatch(file))
            {
                return false; 
            }
        }

        return true; 

    }

};