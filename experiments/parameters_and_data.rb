require 'openssl'

number_of_samples = 10

d = 2;
t = 3;
alpha = 3;
beta = 1;
lambda_ = 20;

gamma = (lambda_ ** 4) / 100
eta = lambda_ ** 2
mu = (gamma - alpha * eta) / beta
sigma = ((alpha * eta - Math.log2(t) - d * beta * mu - d) / d).to_i - 1;

puts "\n\nGiven paramters:"
puts "-------------------------------------"
puts "d = #{d}"
puts "t = #{t}"
puts "alpha = #{alpha}"
puts "beta = #{beta}"
puts "lambda = #{lambda_}\n\n"

puts "Computed parameters:"
puts "-------------------------------------"
puts "gamma = #{gamma}"
puts "eta = #{eta}"
puts "mu = #{mu}"
puts "sigma = #{sigma}\n\n"

q0 = OpenSSL::BN::generate_prime(mu).to_i
p = OpenSSL::BN::generate_prime(eta).to_i
p_to_alpha = p ** alpha
q0_to_beta = q0 ** beta
x0 = p_to_alpha * q0_to_beta

puts "Computed values:"
puts "-------------------------------------"
puts "q0 = #{q0}"
puts "p = #{p}"
puts "p_to_alpha := #{p_to_alpha};"
puts "q0_to_beta := #{q0_to_beta};"
puts "x0 := #{x0};\n\n"

puts "Encryptions:"
puts "-------------------------------------"
ms = Array.new(number_of_samples) { rand(1..50) }
cs = []
ms.each do |m|
  r = OpenSSL::BN::rand(sigma).to_i
  delta = rand(0..(2**gamma) / p_to_alpha)
  c = (delta * p_to_alpha + m + r * q0_to_beta) % x0
  cs << c
  puts "m = #{m}"
  puts "r = #{r}"
  puts "delta = #{delta}"
  puts "c = #{c}\n\n"
end

puts "\n\nCiphertexts:"
puts "-------------------------------------"
puts "Cs := #{cs};\n\n"
