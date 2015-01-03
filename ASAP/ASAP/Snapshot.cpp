#include "stdafx.h"
#include "Snapshot.h"


Snapshot::Snapshot(IntPtr handle, Component^ component)
{
	this->handle = handle;
	this->component = component;
	disposed = false;
}

Snapshot::~Snapshot()
{
	// Dispose of managed resources.
	component->~Component();

	// Call C++ finalizer to clean up unmanaged resources. 
	this->!MyResource();

	// Mark the class as disposed. This flag allows you to throw an 
	// exception if a disposed object is accessed.
	disposed = true;
}