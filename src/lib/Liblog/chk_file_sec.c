/*
*         OpenPBS (Portable Batch System) v2.3 Software License
*
* Copyright (c) 1999-2000 Veridian Information Solutions, Inc.
* All rights reserved.
*
* ---------------------------------------------------------------------------
* For a license to use or redistribute the OpenPBS software under conditions
* other than those described below, or to purchase support for this software,
* please contact Veridian Systems, PBS Products Department ("Licensor") at:
*
*    www.OpenPBS.org  +1 650 967-4675                  sales@OpenPBS.org
*                        877 902-4PBS (US toll-free)
* ---------------------------------------------------------------------------
*
* This license covers use of the OpenPBS v2.3 software (the "Software") at
* your site or location, and, for certain users, redistribution of the
* Software to other sites and locations.  Use and redistribution of
* OpenPBS v2.3 in source and binary forms, with or without modification,
* are permitted provided that all of the following conditions are met.
* After December 31, 2001, only conditions 3-6 must be met:
*
* 1. Commercial and/or non-commercial use of the Software is permitted
*    provided a current software registration is on file at www.OpenPBS.org.
*    If use of this software contributes to a publication, product, or
*    service, proper attribution must be given; see www.OpenPBS.org/credit.html
*
* 2. Redistribution in any form is only permitted for non-commercial,
*    non-profit purposes.  There can be no charge for the Software or any
*    software incorporating the Software.  Further, there can be no
*    expectation of revenue generated as a consequence of redistributing
*    the Software.
*
* 3. Any Redistribution of source code must retain the above copyright notice
*    and the acknowledgment contained in paragraph 6, this list of conditions
*    and the disclaimer contained in paragraph 7.
*
* 4. Any Redistribution in binary form must reproduce the above copyright
*    notice and the acknowledgment contained in paragraph 6, this list of
*    conditions and the disclaimer contained in paragraph 7 in the
*    documentation and/or other materials provided with the distribution.
*
* 5. Redistributions in any form must be accompanied by information on how to
*    obtain complete source code for the OpenPBS software and any
*    modifications and/or additions to the OpenPBS software.  The source code
*    must either be included in the distribution or be available for no more
*    than the cost of distribution plus a nominal fee, and all modifications
*    and additions to the Software must be freely redistributable by any party
*    (including Licensor) without restriction.
*
* 6. All advertising materials mentioning features or use of the Software must
*    display the following acknowledgment:
*
*     "This product includes software developed by NASA Ames Research Center,
*     Lawrence Livermore National Laboratory, and Veridian Information
*     Solutions, Inc.
*     Visit www.OpenPBS.org for OpenPBS software support,
*     products, and information."
*
* 7. DISCLAIMER OF WARRANTY
*
* THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND. ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT
* ARE EXPRESSLY DISCLAIMED.
*
* IN NO EVENT SHALL VERIDIAN CORPORATION, ITS AFFILIATED COMPANIES, OR THE
* U.S. GOVERNMENT OR ANY OF ITS AGENCIES BE LIABLE FOR ANY DIRECT OR INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* This license will be governed by the laws of the Commonwealth of Virginia,
* without reference to its choice of law rules.
*/

#include <pbs_config.h>   /* the master config generated by configure */

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "portability.h"
#include "log.h"
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <string.h>

#ifndef S_ISLNK
#define S_ISLNK(m) (((m) & S_IFMT) == S_IFLNK)
#endif

int chk_file_sec_stderr = 0;


/* 
 * IamRoot returns 1 if current user has root (Administrator) account, 
 * else returns 0
*/
int IamRoot()
  {
#ifndef __CYGWIN__
  if ((getuid() == 0) && (geteuid() == 0))
    {
	return 1;				
    }
  fprintf(stderr, "Must be run as root\n");

#else
  struct group *gr;
  struct passwd *p;
  char **t;

  if (getuid() == 18)
    {
	return 1;
    }
  if ((p = getpwuid(getuid())) == NULL)
    {
	fprintf(stderr, "No password entry for current user. Check your /etc/passwd file.\n");
  	return 0;
    }
  if ((gr=getgrgid(544)) != NULL)
    {
	for (t = gr->gr_mem; t && *t; t++)
	{
	    if (!strcmp (p->pw_name, *t)) 
		return 1;
	}
	fprintf(stderr, "Must be run as user with Administrator privileges\n");
    }
  else
    {
	fprintf(stderr, "No group entry. Check your /etc/group file.\n");
    }
#endif  /* __CYGWIN__ */
  return 0;
  }  /* END IamRoot() */


#ifdef __CYGWIN__
/* 
 * IamAdminByName returns 1 if user <userName> has Administrator account, 
 * else returns 0 
*/
int IamAdminByName(char *userName)
  {
  struct group *gr;
  char **t;

  if ((gr=getgrgid(544)) != NULL)
    {
	for (t = gr->gr_mem; t && *t; t++)
	    if (!strcmp (userName, *t))	
		return 1;
    }
  return 0;
  }  /* END IamAdminByName */



/*
 * IamUser returns 1 if current user isn't included to Administrators group
 * (i.e. has a limited account), else returns 0 
*/
int IamUser()
  {
  struct group *gr;
  struct passwd *p;
  char **t;  

  if ((p = getpwuid(getuid())) && (gr = getgrgid(544)) != NULL)
    {
  	if (getuid() < 1000)
    	{
		return 0;
    	}	
	for (t = gr->gr_mem; t && *t; t++)
	{
	    if (!strcmp (p->pw_name, *t)) 
		return 0;
	}
	return 1;
    }
  log_err(-1, "WARNING!!!", "Check your /etc/group and /etc/passwd files.\n");
  return 0;
  }  /* END IamUser() */



/* 
 * IamUserByName returns 1 if user <userName> isn't included to Administrators group
 * (i.e. has a limited account), else returns 0
*/
int IamUserByName(char *userName)
  {
  struct group *gr;
  char **t;
  char buff[512];

  if ((gr = getgrgid(544)) != NULL)
    {
	for (t = gr->gr_mem; t && *t; t++)
	    if (!strcmp (userName, *t))	
	    {
		sprintf(buff, "Can`t run job with Administrator privileges. Your should limit privileges for \"%s\"", userName);
		log_err(-1, "WARNING!!!", buff);
		return 0;
	    }
	    /* else  log_err(-1,"Try",*t); */
	return 1;
    }
  return 0;
  }  /* END IamUserByName */
#endif /* __CYGWIN__ */




/*
 * chk_file_sec() - Check file/directory security
 *      Part of the PBS System Security "Feature"
 *
 * To be secure, all directories (and final file) in path must be:
 *  owned by uid < 10
 *  owned by group < 10 if group writable
 *  not have world writable unless stick bit set & this is allowed.
 *
 * Returns 0 if ok
 *      errno value if not ok, including:
 *              EPERM if not owned by root
 *              ENOTDIR if not file/directory as specified
 *              EACCESS if permissions are not ok
 */

int chk_file_sec(

  char *path,   /* path to check */
  int   isdir,   /* 1 = path is directory, 0 = file */
  int   sticky,   /* allow write on directory if sticky set */
  int   disallow, /* perm bits to disallow */
  int   fullpath, /* recursively check full path */
  char *SEMsg)    /* O (optional,minsize=1024) */

  {
  int    i;
  char  *error_buf;
  char  *pc;
  int    rc = 0;

  struct stat sbuf;
  char   shorter[_POSIX_PATH_MAX];
  char   symlink[_POSIX_PATH_MAX];

  char   tmpLine[1024];

  char  *EMsg;

  if (SEMsg != NULL)
    EMsg = SEMsg;
  else
    EMsg = tmpLine;

  EMsg[0] = '\0';

  if ((*path == '/') && fullpath)
    {
    /* check full path starting at root */

    strcpy(shorter, path);

    pc = strrchr(shorter, '/');

    if ((pc != NULL) && (pc != shorter))
      {
      /*
       * push "dirname" onto stack, stack will pop back from
       * root to the given file/directory
       */

      *pc = '\0';

      if ((rc = chk_file_sec(shorter, 1, sticky, S_IWGRP | S_IWOTH, 1, EMsg)) != 0)
        {
        return(rc);
        }
      }
    }

  if (lstat(path, &sbuf) == -1)
    {
    rc = errno;

    /* FAILURE */

    if (EMsg != NULL)
      snprintf(EMsg, 1024, "%s cannot be lstat'd - errno=%d, %s",
               path,
               rc,
               strerror(rc));

    goto chkerr;
    }

  if (S_ISLNK(sbuf.st_mode) != 0)
    {
    i = readlink(
          path,
          symlink,  /* O */
          _POSIX_PATH_MAX);

    if (i < 0)
      {
      rc = errno;

      /* FAILURE */

      snprintf(EMsg, 1024, "%s cannot be read as link, errno=%d, %s",
               path,
               rc,
               strerror(rc));

      goto chkerr;
      }

    symlink[i] = '\0';

    if (symlink[0] == '/')
      {
      return(chk_file_sec(symlink, isdir, sticky, disallow, fullpath, EMsg));
      }

    strcpy(shorter, path);

    /* terminate string after final directory delimiter */

    pc = strrchr(shorter, '/');

    if (pc != NULL)
      {
      pc[1] = '\0';
      }

    /* now figure out how to follow the symlink */

    if (stat(path, &sbuf) == -1)
      {
      rc = errno;

      /* FAILURE */

      snprintf(EMsg, 1024, "%s cannot be stat'd - errno=%d, %s",
               path,
               rc,
               strerror(rc));

      goto chkerr;
      }

    if (S_ISDIR(sbuf.st_mode) != 0)
      {
      strcat(shorter, symlink);
      }
    else
      {
      strcpy(shorter, symlink);
      }

    return(chk_file_sec(shorter, isdir, sticky, disallow, fullpath, EMsg));
    }

  i = sbuf.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);

#ifndef __CYGWIN__
  if (sbuf.st_uid > 10)
    {
    rc = EPERM;

    /* FAILURE */

    snprintf(EMsg, 1024, "%s is not owned by admin user",
             path);
    }
  else 
#endif  /* __CYGWIN__ */

    if (((isdir == 1) && (S_ISDIR(sbuf.st_mode) == 0)) ||
           ((isdir == 0) && (S_ISREG(sbuf.st_mode) == 0)))
    {
    /* FAILURE */

    snprintf(EMsg, 1024, "%s is not directory",
             path);

    rc = ENOTDIR;
    }
  else if (isdir && sticky && !fullpath)
    {
    if ((S_ISDIR(sbuf.st_mode) == 0) ||
        ((sbuf.st_mode & S_ISVTX) == 0) ||
        (i != (S_IRWXU | S_IRWXG | S_IRWXO)))
      {
      /* FAILURE */

      snprintf(EMsg, 1024, "%s cannot be accessed",
               path);

      rc = EACCES;
      }
    }
  else if (i & disallow)
    {
    /* if group write, gid must be less than 10 */

#ifndef __CYGWIN__
    if ((i & disallow & S_IWGRP) && (sbuf.st_gid > 9))
      {
      /* FAILURE */

      snprintf(EMsg, 1024, "%s is group writable",
               path);

      rc = EPERM;
      }
#endif  /* __CYGWIN__ */

    /* if world write, sticky bit must be set and "sticky" ok */

    if (i & disallow & S_IWOTH)
      {
      if ((S_ISDIR(sbuf.st_mode) == 0) ||
          (((sbuf.st_mode & S_ISVTX) == 0) || (sticky != 1)))
        {
        /* FAILURE */

        snprintf(EMsg, 1024, "%s is world writable and not sticky",
                 path);

        rc = EACCES;
        }
      }

    /* check any remaining bits */

    if (i & disallow & ~(S_IWGRP | S_IWOTH))
      {
      /* FAILURE */

      snprintf(EMsg, 1024, "%s is writable by group or other",
               path);

      rc = EACCES;
      }
    }

chkerr:

  if (rc != 0)
    {
    if ((error_buf = malloc(LOG_BUF_SIZE)) == NULL)
      {
      if (chk_file_sec_stderr)
        {
        fprintf(stdout, "chk_tree: Malloc failed: error #%d: (%s)\n",
                rc,
                strerror(rc) ? strerror(rc) : "UNKNOWN");
        }
      else
        {
        log_err(rc, "chk_file_sec", "Malloc failed");
        }
      }
    else
      {
      if (EMsg[0] != '\0')
        {
        sprintf(error_buf, "Security violation with \"%s\" - %s",
                path,
                EMsg);
        }
      else
        {
        sprintf(error_buf, "Security violation with \"%s\", errno=%d, %s",
                path,
                rc,
                strerror(rc));
        }

      if (chk_file_sec_stderr)
        {
        fprintf(stdout, "chk_tree: %s: error #%d: (%s)\n",
                error_buf,
                rc,
                strerror(rc) ? strerror(rc) : "UNKNOWN");
        }
      else
        {
        log_err(rc, "chk_file_sec",
                error_buf);
        }

      free(error_buf);
      }
    }    /* END if (rc != 0) */

  return(rc);
  }  /* END chk_sec_file.c */

/* END chk_file_sec.c */
