//
// Module that implements a file that will be preloaded at file system. 
// It is defined by a tenant in order to be loaded and modified by an application
//
// @author Gabriel Gonzalez Casta;&ntilde;e
// @date 2012-11-30

package icancloud.src.Users.UserGenerator.PreloadFilesDefinition;

simple PreloadFilesDefinition
{
   parameters:
       string name;
       int size_KiB;
}