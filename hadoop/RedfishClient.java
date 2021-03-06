/*
 * Copyright 2011-2012 the Redfish authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.apache.hadoop.fs.redfish;

import java.io.*;
import java.net.*;

import org.apache.commons.logging.Log;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.BlockLocation;
import org.apache.hadoop.fs.FSDataInputStream;
import org.apache.hadoop.fs.FSDataOutputStream;
import org.apache.hadoop.fs.FileStatus;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.FileUtil;
import org.apache.hadoop.fs.Path;


final class RedfishClient {
  private long m_cli;

  static {
    try {
      System.loadLibrary("hfishc");
    }
    catch (UnsatisfiedLinkError e) {
      e.printStackTrace();
      System.err.println("Unable to load hfishc: " +
                System.getProperty("java.library.path"));
      System.exit(1);
    }
  }

  public RedfishClient(String configFile, String userName) throws IOException {
    this.redfishConnect(configFile, userName);
  }

  /* This finalizer is intended to free the (small!) amount of memory used by
   * the redfish_client data structure of a disconnected client.  It also
   * destroys the pthread mutex used to make the rest of the functions
   * thread-safe.
   *
   * Please call redfishDisconnect explicitly to tear down connections.  This
   * it NOT intended as a replacement for that function.
   * */
  protected void finalize() throws Throwable {} {
    this.redfishRelease();
  }

  private final native
    String redfishConnect(String configFile, String userName) throws IOException;

  private final native
    void redfishRelease();

  public final native
    RedfishDataOutputStream redfishCreate(String jpath, short mode,
      int bufsz, short repl, long blocksz) throws IOException;

  public final native
    RedfishDataInputStream redfishOpen(String jpath) throws IOException;

  public final native
    boolean redfishMkdirs(String jpath, short mode) throws IOException;

  public final native
    BlockLocation[] redfishGetBlockLocations(String jpath, long start, long len)
      throws IOException;

  public final native
    FileStatus redfishGetPathStatus(String jpath) throws IOException;

  public final native
    FileStatus[] redfishListDirectory(String jpath) throws IOException;

  public final native
    void redfishChmod(String jpath, short mode) throws IOException;

  public final native
    void redfishChown(String jpath, String owner, String group)
      throws IOException;

  public final native
    void redfishUtimes(String jpath, long mtime, long atime) throws IOException;

  public final native
    void redfishDisconnect() throws IOException;

  public final native
    boolean redfishUnlink(String jpath) throws IOException;

  public final native
    boolean redfishUnlinkTree(String jpath) throws IOException;

  public final native
    boolean redfishRename(String src, String dst) throws IOException;
};
