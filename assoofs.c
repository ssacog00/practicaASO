#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO  */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/fs.h>           /* libfs stuff           */
//#include <asm/uaccess.h>        /* copy_to_user          */
#include <linux/buffer_head.h>  /* buffer_head           */
#include <linux/slab.h>         /* kmem_cache            */
#include "assoofs.h"

MODULE_LICENSE("GPL_v2");
MODULE_AUTHOR("Sergio Saco Garcia");


extern int register_filesystem ( struct file_system_type *) ;
extern int unregister_filesystem ( struct file_system_type *) ;

static int __init assoofs_init(void)
{
	int ret;
	assofs_inode_cache = kmem_cache_create("assosfs_inode_cache"), sizeof(struct assoofs_inode_info), 0, (SLAB_RECLAIM_ACCOUNT |SLAB_MEM_SPREAD), NULL);

	if(!assoofs_inode_cache) return -ENOMEN; //ENOMEN (valor 12) significa fuera de memoria

	ret = register_filesystem(&assoofs_type);

	if(ret==0)
	    printk(KERN_INFO "Sucessfully registered assoofs\n");
	else
	    printk(KERN_ERR "Failed to register assoofs. Error %d",ret);

	return ret;
}

static void __exit assoofs_exit(void)
{
	int ret;
	ret = unregister_flesystem(&assoofs_type);
	kmem_cache_destroy(assoofs_inode_cache);

	if(ret==0)
	    printk(KERN_INFO "Sucessfully unregistered assoofs\n");
	else
	    printk(KERN_ERR "Failed to unregister assoofs. Error %d",ret);

}

module_init(assoofs_init);
module_exit(assoofs_exit);
