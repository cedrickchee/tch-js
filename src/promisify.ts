type CallbackErr = Error | string | null;
type Callback<R> = (err: CallbackErr, result: R) => any;

type FunctionWithCallback<T extends any[], R> = (
  ...args: [Callback<R>, ...T[]]
) => any;

const promisifyCallback = <I extends any[], R>(
  func: FunctionWithCallback<I, R>
) => (...args: I): Promise<R> => {
  return new Promise((resolve, reject) => {
    func((err: CallbackErr, result: R) => {
      return err ? reject(err) : resolve(result);
    }, ...args);
  });
};

export { promisifyCallback as promisify };
