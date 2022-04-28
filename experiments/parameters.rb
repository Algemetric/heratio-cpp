require 'openssl'

d = 20;
t = 5;
alpha = 6;
beta = 2;
lambda_ = 64;

gamma = (lambda_ ** 5) / 12000
eta = 15639
mu = 1280
rho = beta * mu + lambda_
r = lambda_

eta_reference = (lambda_**2 + rho * lambda_) / 11

# tau = ((beta * mu - (log2(t)).ceil + 2 * d) / d).to_i - 1;

real_gamma = eta * alpha + mu * beta


puts "Tests:"
puts "-------------------------------------"
puts "rho valid? #{rho >= (lambda_)} | actual: #{rho}, reference: #{(lambda_)}"
puts "eta valid? #{eta >= eta_reference} | actual: #{eta}, reference: #{eta_reference}"
puts "real_gamma valid? #{real_gamma >= (gamma)}  | actual: #{real_gamma}, reference: #{(gamma)}"
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