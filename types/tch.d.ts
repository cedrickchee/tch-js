interface ScriptModule {
  forward(input: any, callback: Result): void;
}
interface Tensor {
  toUint8Array(): Uint8Array;
  toFloat32Array(): Float32Array;
}
type Result = (err: Error, result: Tensor) => void;
