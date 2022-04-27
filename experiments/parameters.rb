require 'openssl'

d = 15;
t = 3;
alpha = 6;
beta = 3;
lambda_ = 50;

gamma = (lambda_ ** 4) / 100
eta = lambda_ ** 2
mu = (gamma - alpha * eta) / beta
sigma = ((alpha * eta - Math.log2(t) - d * beta * mu - d) / d).to_i - 1;
# tau = ((beta * mu - (log2(t)).ceil + 2 * d) / d).to_i - 1;

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

# puts "sigma = #{sigma}"
# puts "tau = #{tau}\n\n"