#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <string>
#include <sstream>

#include "pbs_error.h"
#include "attr_req_info.hpp"

const char *LPROCS     = "lprocs";
const char *NODES      = "node";
const char *SOCKETS    = "socket";
const char *NUMA_CHIPS = "numachip";
const char *CORES      = "core";
const char *THREADS    = "thread";
const char *MEMORY     = "memory";
const char *SWAP       = "swap";
const char *DISK       = "disk";


attr_req_info& attr_req_info::operator= (const attr_req_info& newattr_req_info)
  {
  if (this == &newattr_req_info)
    return *this;

  max_lprocs = newattr_req_info.max_lprocs;
  max_mem = newattr_req_info.max_mem;
  max_swap = newattr_req_info.max_swap;
  max_disk = newattr_req_info.max_disk;
  max_nodes = newattr_req_info.max_nodes;
  max_sockets = newattr_req_info.max_sockets;
  max_cores = newattr_req_info.max_cores;
  max_numa_chips = newattr_req_info.max_numa_chips;
  max_threads = newattr_req_info.max_threads;

  min_lprocs = newattr_req_info.min_lprocs;
  min_mem = newattr_req_info.min_mem;
  min_swap = newattr_req_info.min_swap;
  min_disk = newattr_req_info.min_disk;
  min_nodes = newattr_req_info.min_nodes;
  min_sockets = newattr_req_info.min_sockets;
  min_cores = newattr_req_info.min_cores;
  min_numa_chips = newattr_req_info.min_numa_chips;
  min_threads = newattr_req_info.min_threads;

  default_lprocs = newattr_req_info.default_lprocs;
  default_mem = newattr_req_info.default_mem;
  default_swap = newattr_req_info.default_swap;
  default_disk = newattr_req_info.default_disk;
  default_nodes = newattr_req_info.default_nodes;
  default_sockets = newattr_req_info.default_sockets;
  default_cores = newattr_req_info.default_cores;
  default_numa_chips = newattr_req_info.default_numa_chips;
  default_threads = newattr_req_info.default_threads;

  return *this; 
  }

attr_req_info::attr_req_info() : max_lprocs(0), max_mem(0), max_swap(0), max_disk(0), max_nodes(0),
                                 max_sockets(0), max_cores(0), max_numa_chips(0), max_threads(0),
                                 min_lprocs(0), min_mem(0), min_swap(0), min_disk(0), min_nodes(0),
                                 min_sockets(0), min_cores(0), min_numa_chips(0), min_threads(0),
                                 default_lprocs(0), default_mem(0), default_swap(0), default_disk(0), default_nodes(0),
                                 default_sockets(0), default_cores(0), default_numa_chips(0), default_threads(0)
   {
   }

attr_req_info::~attr_req_info()
  {
  }


int attr_req_info::set_min_limit_value(

  const char *rescn,
  const char *val)

  {
  /* Just go through the list of keywords and set the appropriate value */
  if (!strncmp(rescn, LPROCS, strlen(LPROCS)))
    {
    min_lprocs = atoi(val);
    }
  else if (!strncmp(rescn, MEMORY, strlen(MEMORY)))
    {
    min_mem = strtoul(val, NULL, 0);
    }
  else if (!strncmp(rescn, SWAP, strlen(SWAP)))
    {
    min_swap = strtoul(val, NULL, 0);
    }
  else if (!strncmp(rescn, DISK, strlen(DISK)))
    {
    min_disk = strtoul(val, NULL, 0);
    }
  else if (!strncmp(rescn, NODES, strlen(NODES)))
    {
    min_nodes = atoi(val);
    }
  else if (!strncmp(rescn, SOCKETS, strlen(SOCKETS)))
    {
    min_sockets = atoi(val);
    }
  else if (!strncmp(rescn, CORES, strlen(CORES)))
    {
    min_cores = atoi(val);
    }
  else if (!strncmp(rescn, NUMA_CHIPS, strlen(NUMA_CHIPS)))
    {
    min_numa_chips = atoi(val);
    }
  else if (!strncmp(rescn, THREADS, strlen(THREADS)))
    {
    min_threads = atoi(val);
    }
  else
    return(PBSE_BAD_PARAMETER);

  return(PBSE_NONE);

  }


 int attr_req_info::set_max_limit_value(

  const char *rescn,
  const char *val)

  {
  /* Just go through the list of keywords and set the appropriate value */
   if (!strncmp(rescn, LPROCS, strlen(LPROCS)))
    {
    max_lprocs = atoi(val);
    }
  else if (!strncmp(rescn, MEMORY, strlen(MEMORY)))
    {
    max_mem = strtoul(val, NULL, 0);
    }
  else if (!strncmp(rescn, SWAP, strlen(SWAP)))
    {
    max_swap = strtoul(val, NULL, 0);
    }
  else if (!strncmp(rescn, DISK, strlen(DISK)))
    {
    max_disk = strtoul(val, NULL, 0);
    }
  else if (!strncmp(rescn, NODES, strlen(NODES)))
    {
    max_nodes = atoi(val);
    }
  else if (!strncmp(rescn, SOCKETS, strlen(SOCKETS)))
    {
    max_sockets = atoi(val);
    }
  else if (!strncmp(rescn, CORES, strlen(CORES)))
    {
    max_cores = atoi(val);
    }
  else if (!strncmp(rescn, NUMA_CHIPS, strlen(NUMA_CHIPS)))
    {
    max_numa_chips = atoi(val);
    }
  else if (!strncmp(rescn, THREADS, strlen(THREADS)))
    {
    max_threads = atoi(val);
    }
  else
    return(PBSE_BAD_PARAMETER);

  return(PBSE_NONE);

   }

 int attr_req_info::set_default_limit_value(

  const char *rescn,
  const char *val)

  {
  /* Just go through the list of keywords and set the appropriate value */
  if (!strncmp(rescn, LPROCS, strlen(LPROCS)))
    {
    default_lprocs = atoi(val);
    }
  else if (!strncmp(rescn, MEMORY, strlen(MEMORY)))
    {
    default_mem = strtoul(val, NULL, 0);
    }
  else if (!strncmp(rescn, SWAP, strlen(SWAP)))
    {
    default_swap = strtoul(val, NULL, 0);
    }
  else if (!strncmp(rescn, DISK, strlen(DISK)))
    {
    default_disk = strtoul(val, NULL, 0);
    }
  else if (!strncmp(rescn, NODES, strlen(NODES)))
    {
    default_nodes = atoi(val);
    }
  else if (!strncmp(rescn, SOCKETS, strlen(SOCKETS)))
    {
    default_sockets = atoi(val);
    }
  else if (!strncmp(rescn, CORES, strlen(CORES)))
    {
    default_cores = atoi(val);
    }
  else if (!strncmp(rescn, NUMA_CHIPS, strlen(NUMA_CHIPS)))
    {
    default_numa_chips = atoi(val);
    }
  else if (!strncmp(rescn, THREADS, strlen(THREADS)))
    {
    default_threads = atoi(val);
    }
  else
    return(PBSE_BAD_PARAMETER);

  return(PBSE_NONE);

   }


int attr_req_info::get_signed_min_limit_value(

  const char *rescn,
  int& value)

  { 
  if (!strncmp(rescn, LPROCS, strlen(LPROCS)))
    {
    value = min_lprocs;
    }
  else if (!strncmp(rescn, NODES, strlen(NODES)))
    {
    value = min_nodes;
    }
  else if (!strncmp(rescn, SOCKETS, strlen(SOCKETS)))
    {
    value = min_sockets;
    }
  else if (!strncmp(rescn, NUMA_CHIPS, strlen(NUMA_CHIPS)))
    {
    value = min_numa_chips;
    }
  else if (!strncmp(rescn, CORES, strlen(CORES)))
    {
    value = min_cores;
    }
  else if (!strncmp(rescn, THREADS, strlen(THREADS)))
    {
    value = min_threads;
    }
  else
    return (PBSE_BAD_PARAMETER);

  return(PBSE_NONE);
  }

unsigned int attr_req_info::get_unsigned_min_limit_value(

  const char *rescn,
  unsigned int& value)

  {
  if (!strncmp(rescn, MEMORY, strlen(MEMORY)))
    {
    value = min_mem;
    }
  else if (!strncmp(rescn, SWAP, strlen(SWAP)))
    {
    value = min_swap;
    }
  else if (!strncmp(rescn, DISK, strlen(DISK)))
    {
    value = min_disk;
    }
  else
    return (PBSE_BAD_PARAMETER);

  return(PBSE_NONE);
  }

int attr_req_info::get_signed_max_limit_value(

  const char *rescn,
  int& value)

  {
  if (!strncmp(rescn, LPROCS, strlen(LPROCS)))
    {
    value = max_lprocs;
    }
  else if (!strncmp(rescn, NODES, strlen(NODES)))
    {
    value = max_nodes;
    }
  else if (!strncmp(rescn, SOCKETS, strlen(SOCKETS)))
    {
    value = max_sockets;
    }
  else if (!strncmp(rescn, NUMA_CHIPS, strlen(NUMA_CHIPS)))
    {
    value = max_numa_chips;
    }
  else if (!strncmp(rescn, CORES, strlen(CORES)))
    {
    value = max_cores;
    }
  else if (!strncmp(rescn, THREADS, strlen(THREADS)))
    {
    value = max_threads;
    }
  else
    return (PBSE_BAD_PARAMETER);

  return(PBSE_NONE);
  }

unsigned int attr_req_info::get_unsigned_max_limit_value(

  const char *rescn,
  unsigned int& value)

  {
  if (!strncmp(rescn, MEMORY, strlen(MEMORY)))
    {
    value = max_mem;
    }
  else if (!strncmp(rescn, SWAP, strlen(SWAP)))
    {
    value = max_swap;
    }
  else if (!strncmp(rescn, DISK, strlen(DISK)))
    {
    value = max_disk;
    }
  else
    return (PBSE_BAD_PARAMETER);

  return(PBSE_NONE);
  }

int attr_req_info::get_signed_default_limit_value(

  const char *rescn,
  int& value)

  {
  if (!strncmp(rescn, LPROCS, strlen(LPROCS)))
    {
    value = default_lprocs;
    }
  else if (!strncmp(rescn, NODES, strlen(NODES)))
    {
    value = default_nodes;
    }
  else if (!strncmp(rescn, SOCKETS, strlen(SOCKETS)))
    {
    value = default_sockets;
    }
  else if (!strncmp(rescn, NUMA_CHIPS, strlen(NUMA_CHIPS)))
    {
    value = default_numa_chips;
    }
  else if (!strncmp(rescn, CORES, strlen(CORES)))
    {
    value = default_cores;
    }
  else if (!strncmp(rescn, THREADS, strlen(THREADS)))
    {
    value = default_threads;
    }
  else
    return (PBSE_BAD_PARAMETER);

  return(PBSE_NONE);
  }

unsigned int attr_req_info::get_unsigned_default_limit_value(

  const char *rescn,
  unsigned int& value)

  {
  if (!strncmp(rescn, MEMORY, strlen(MEMORY)))
    {
    value = default_mem;
    }
  else if (!strncmp(rescn, SWAP, strlen(SWAP)))
    {
    value = default_swap;
    }
  else if (!strncmp(rescn, DISK, strlen(DISK)))
    {
    value = default_disk;
    }
  else
    return (PBSE_BAD_PARAMETER);

  return(PBSE_NONE);
  }


int attr_req_info::get_max_values(std::vector<std::string>& names, std::vector<std::string>& values)
  {
  char buf[100];

  if (max_lprocs != 0)
    {
    sprintf(buf, "%s", LPROCS );
    names.push_back(buf);
    sprintf(buf, "%d", max_lprocs);
    values.push_back(buf);
    }

  if (max_mem != 0)
    {
    sprintf(buf, "%s", MEMORY);
    names.push_back(buf);
    sprintf(buf, "%ukb", max_mem);
    values.push_back(buf);
    }

  if (max_swap != 0)
    {
    sprintf(buf, "%s", SWAP);
    names.push_back(buf);
    sprintf(buf, "%ukb", max_swap);
    values.push_back(buf);
    }

  if (max_disk != 0)
    {
    sprintf(buf, "%s", DISK);
    names.push_back(buf);
    sprintf(buf, "%ukb", max_disk);
    values.push_back(buf);
    }

  if (max_nodes != 0)
    {
    sprintf(buf, "%s", NODES);
    names.push_back(buf);
    sprintf(buf, "%d", max_nodes);
    values.push_back(buf);
    }

  if (max_sockets != 0)
    {
    sprintf(buf, "%s", SOCKETS);
    names.push_back(buf);
    sprintf(buf, "%d", max_sockets);
    values.push_back(buf);
    }

  if (max_numa_chips != 0)
    {
    sprintf(buf, "%s", NUMA_CHIPS);
    names.push_back(buf);
    sprintf(buf, "%d", max_numa_chips);
    values.push_back(buf);
    }

  if (max_cores != 0)
    {
    sprintf(buf,"%s", CORES);
    names.push_back(buf);
    sprintf(buf, "%d", max_cores);
    values.push_back(buf);
    }

  if (max_threads != 0)
    {
    sprintf(buf, "%s", THREADS);
    names.push_back(buf);
    sprintf(buf, "%d", max_threads);
    values.push_back(buf);
    }

  return(PBSE_NONE);
  }

int attr_req_info::get_min_values(std::vector<std::string>& names, std::vector<std::string>& values)
  {
  char buf[100];

  if (min_lprocs != 0)
    {
    sprintf(buf, "%s", LPROCS);
    names.push_back(buf);
    sprintf(buf, "%d", min_lprocs);
    values.push_back(buf);
    }

  if (min_mem != 0)
    {
    sprintf(buf, "%s", MEMORY);
    names.push_back(buf);
    sprintf(buf, "%ukb", min_mem);
    values.push_back(buf);
    }

  if (min_swap != 0)
    {
    sprintf(buf, "%s", SWAP);
    names.push_back(buf);
    sprintf(buf, "%ukb", min_swap);
    values.push_back(buf);
    }

  if (min_disk != 0)
    {
    sprintf(buf, "%s", DISK);
    names.push_back(buf);
    sprintf(buf, "%ukb", min_disk);
    values.push_back(buf);
    }

  if (min_nodes != 0)
    {
    sprintf(buf, "%s", NODES);
    names.push_back(buf);
    sprintf(buf, "%d", min_nodes);
    values.push_back(buf);
    }

  if (min_sockets != 0)
    {
    sprintf(buf, "%s", SOCKETS);
    names.push_back(buf);
    sprintf(buf, "%d", min_sockets);
    values.push_back(buf);
    }

  if (min_numa_chips != 0)
    {
    sprintf(buf, "%s", NUMA_CHIPS);
    names.push_back(buf);
    sprintf(buf, "%d", min_numa_chips);
    values.push_back(buf);
    }


  if (min_cores != 0)
    {
    sprintf(buf, "%s", CORES);
    names.push_back(buf);
    sprintf(buf, "%d", min_cores);
    values.push_back(buf);
    }

  if (min_threads != 0)
    {
    sprintf(buf, "%s", THREADS);
    names.push_back(buf);
    sprintf(buf, "%d", min_threads);
    values.push_back(buf);
    }

  return(PBSE_NONE);
  }


int attr_req_info::get_default_values(std::vector<std::string>& names, std::vector<std::string>& values)
  {
  char buf[100];

  if (default_lprocs != 0)
    {
    sprintf(buf, "%s", LPROCS);
    names.push_back(buf);
    sprintf(buf, "%d", default_lprocs);
    values.push_back(buf);
    }

  if (default_mem != 0)
    {
    sprintf(buf, "%s", MEMORY);
    names.push_back(buf);
    sprintf(buf, "%ukb", default_mem);
    values.push_back(buf);
    }

  if (default_swap != 0)
    {
    sprintf(buf, "%s", SWAP);
    names.push_back(buf);
    sprintf(buf, "%ukb", default_swap);
    values.push_back(buf);
    }

  if (default_disk != 0)
    {
    sprintf(buf, "%s", DISK);
    names.push_back(buf);
    sprintf(buf, "%ukb", default_disk);
    values.push_back(buf);
    }

  if (default_nodes != 0)
    {
    sprintf(buf, "%s", NODES);
    names.push_back(buf);
    sprintf(buf, "%d", default_nodes);
    values.push_back(buf);
    }

  if (default_sockets != 0)
    {
    sprintf(buf, "%s", SOCKETS);
    names.push_back(buf);
    sprintf(buf, "%d", default_sockets);
    values.push_back(buf);
    }

  if (default_numa_chips != 0)
    {
    sprintf(buf, "%s", NUMA_CHIPS);
    names.push_back(buf);
    sprintf(buf, "%d", default_numa_chips);
    values.push_back(buf);
    }

  if (default_cores != 0)
    {
    sprintf(buf, "%s", CORES);
    names.push_back(buf);
    sprintf(buf, "%d", default_cores);
    values.push_back(buf);
    }

  if (default_threads != 0)
    {
    sprintf(buf, "%s", THREADS);
    names.push_back(buf);
    sprintf(buf, "%d", default_threads);
    values.push_back(buf);
    }

  return(PBSE_NONE);
  }


int attr_req_info::check_max_values(

  std::vector<std::string>& names, 
  std::vector<std::string>& values)

  {
  int ret;
  int          signed_value;
  unsigned int unsigned_value;


  for (unsigned int i = 0; i < names.size(); i++)
    {
    signed_value = 0;
    unsigned_value = 0;
    ret = this->get_signed_max_limit_value(names[i].c_str(), signed_value);
    if ((ret == PBSE_NONE) && (signed_value != 0))
      {
      int val;

      val = atoi(values[i].c_str());
      if (val > signed_value)
        {
        return(PBSE_EXLIMIT);
        }
      }
        
    ret = this->get_unsigned_max_limit_value(names[i].c_str(), unsigned_value);
    if ((ret == PBSE_NONE) && (unsigned_value != 0))
      {
      unsigned int uval;
      std::stringstream s(values[i].c_str());

      s >> uval;
      if (uval > unsigned_value)
        {
        return(PBSE_EXLIMIT);
        }
      }
    }
  
  return(PBSE_NONE);
  }

int attr_req_info::check_min_values(

  std::vector<std::string>& names, 
  std::vector<std::string>& values)

  {
  int ret;
  int          signed_value;
  unsigned int unsigned_value;


  for (unsigned int i = 0; i < names.size(); i++)
    {
    signed_value = 0;
    unsigned_value = 0;
    ret = this->get_signed_min_limit_value(names[i].c_str(), signed_value);
    if ((ret == PBSE_NONE) && (signed_value != 0))
      {
      int val;

      val = atoi(values[i].c_str());
      if (val < signed_value)
        {
        return(PBSE_EXLIMIT);
        }
      }
        
    ret = this->get_unsigned_min_limit_value(names[i].c_str(), unsigned_value);
    if ((ret == PBSE_NONE) && (unsigned_value != 0))
      {
      unsigned int uval;
      std::stringstream s(values[i].c_str());

      s >> uval;
      if (uval < unsigned_value)
        {
        return(PBSE_EXLIMIT);
        }
      }
    }
 
  return(PBSE_NONE);
  }


/* 
 * check_default_values
 *
 * compares the value name and value to currently set default limits.
 * If the limits exist return PBSE_NONE if the value is >= limit.
 * Otherwise return PBSE_EXLIMIT indicating the value is less than
 * the default limit.
 *
 * @param name - name of resource limit to check
 * @param value - string representation of the value
 * @param signed_val - value of current signed limit value of the name resoruce if set returned
 * @param unsigned_val - value of current unsigned limit of the name resource if set.
 */
int attr_req_info::add_default_values(

  std::vector<std::string>& names,
  std::vector<std::string>& values,
  std::vector<std::string>& names_to_add,
  std::vector<std::string>& values_to_add)

  {
  std::vector<std::string> default_names;
  std::vector<std::string> default_values;

  /* Get all of the default values that have been set on the queue */
  this->get_default_values(default_names, default_values);

  /* iterate over each default value that is set in the queue and 
   * see if there is a match in the users req
   */
  for (unsigned int i = 0; i < default_names.size(); i++)
    {
    bool found;

    found = false;
    for (unsigned int j = 0; j < names.size(); j++)
      {
      std::string dflt_name = default_names[i].c_str();
      std::string req_name = names[j].c_str();

      if (!strncmp(dflt_name.c_str(), req_name.c_str(), strlen(dflt_name.c_str())))
        {
        found = true;
        break;
        }

      }
    if (found == false)
      {
      names_to_add.push_back(default_names[i]);
      values_to_add.push_back(default_values[i]);
      }
    }

 
  return(PBSE_NONE);
  }


