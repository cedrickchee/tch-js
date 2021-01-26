import torch

def matmul(x):
  return x * 2

torch.jit.trace(matmul, torch.randn(3, 3)).save("matmul.pt")