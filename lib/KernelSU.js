const { BaseKernelSU } = require("bindings")("ksu.node");

/*
 * Simple class to manage KernelSU
 */
class KernelSU extends BaseKernelSU {
   constructor() {
      super();
   }

   /*
    * @param {string} pkg Package name
    * @returns {boolean}
    */
   static becomeManager(pkg) {
      return super.becomeManager(pkg)
   }

   /*
    * Return the current version of KernelSU
    * @returns {number}
    */
   static getVersion() {
      return super.getVersion()
   }

   /*
    * Return a array of allowed root apos
    * @returns {Array<number<}
    */
   static getAllowList() {
      return super.getAllowList()
   }

   /*
    * @param {number} pkg Package name
    * @returns {boolean}
    */
   static uidShouldUnmount(uid) {
      return super.uidShouldUnmount(uid)
   }

   /*
    * @returns {boolean}
    */
   static isSafeMode() {
      return super.isSafeMode()
   }

   /*
    * Node.js cant offer this support or required to much effort to make it work.
    */
   static setAppProfile() {
      throw new Error('Unsupported')
   }

   /*
    * Node.js cant offer this support or required to much effort to make it work.
    */
   static getAppProfile() {
      throw new Error('Unsupported')
   }
}

module.exports = {
   KernelSU
};