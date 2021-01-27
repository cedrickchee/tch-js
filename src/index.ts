import tch from './binding';
// import * as types from 'types';
import { promisify } from './promisify';

// const load = (filePath: string) => {
//   return new Promise((resolve, reject) => {
//     tch.load(filePath, (err: Error | null, model: Model) => {
//       if (err) reject(err);
//       return resolve(model);
//     })
//   });
// };

// [path: string]
let loadAsPromise = promisify<any, ScriptModule>(tch.load);
type tsr = Tensor;

export { tch, loadAsPromise as load, tsr as Tensor };
