#!/usr/bin/env python3

import inspect
import os
import subprocess
import sys


class Test:

	def __init__(self, cmd, out="", err=""):
		self.cmd = cmd
		self.expected_out = out
		self.expected_err = err

		if self.expected_out and self.expected_out[-1] != '\n':
			self.expected_out += '\n'
		if self.expected_err and self.expected_err[-1] != '\n':
			self.expected_err += '\n'
			
	def run(self):
		p = subprocess.Popen(
			["./minishell", "-c", self.cmd],
			stdin=subprocess.PIPE,
			stdout=subprocess.PIPE,
			stderr=subprocess.PIPE
		)

		p.stdin.close()
		p.wait()

		self.returncode = p.returncode
		self.actual_out = p.stdout.read().decode()
		self.actual_err = p.stderr.read().decode()
		
		return (
			self.returncode == 0 and
			self.actual_out == self.expected_out and
			self.actual_err == self.expected_err
		)

	@property
	def trace(self):
		return (
			f"    > {self.cmd}\n"
			f"    returned {self.returncode}\n"
			f"    stdout: {repr(self.actual_out):9s} (expected {repr(self.expected_out)})\n"
			f"    stderr: {repr(self.actual_err):9s} (expected {repr(self.expected_err)})\n\n"
		)


class CompareTest(Test):

	def __init__(self, cmd, cmd_sh=None):
		super().__init__(cmd)
		self.cmd_sh = cmd_sh if cmd_sh else cmd

	def run(self):
		self.get_expected()
		super().run()

	def get_expected(self):
		p = subprocess.Popen(
			["sh", "-c", self.cmd_sh],
			stdin=subprocess.PIPE,
			stdout=subprocess.PIPE,
			stderr=subprocess.PIPE
		)

		p.stdin.close()
		p.wait()

		self.expected_out = p.stdout.read().decode()
		self.expected_err = p.stderr.read().decode()


class CustomTest(Test):

	def __init__(self, cmd, fun):
		self.fun = fun
		super().__init__(cmd)

	def run(self):
		super().run()
		return (
			self.returncode == 0 and
			self.fun(self.actual_out, self.actual_err)
		)

	@property
	def trace(self):
		return (
			f"    > {self.cmd}\n"
			f"    returned {self.returncode}\n"
			f"    stdout: {repr(self.actual_out):9s}\n"
			f"    stderr: {repr(self.actual_err):9s}\n"
			f"    function: {inspect.getsource(self.fun)}\n\n"
		)
	

class Suite:
	
	suites = list()

	def __init__(self, name):
		self.name = name
		self.tests = list()
		self.nsuccess = 0
		Suite.suites.append(self)
	
	def add(self, test):
		self.tests.append(test)
	
	def run(self):
		print (f"Running '{self.name}': ")
	
		for test in self.tests:
			if test.run() is False:
				print('✗', end="")
				for _ in range(len(self.tests) - 1 - self.nsuccess):
					print('⚬', end="")
			
				print(f"\n\nTrace:\n{test.trace}")
				return False
			
			print(u'✓', end='')
			self.nsuccess += 1
		
		print("\n")
		return True
	
	@classmethod
	def run_suites(cls):
		nsuccess = 0
		for suite in cls.suites:
			nsuccess += suite.run()
		
		nfail = len(cls.suites) - nsuccess
		ntest_total = sum(len(suite.tests) for suite in cls.suites)
		print(f"ran {ntest_total} tests, {nsuccess} suites succeeded, {nfail} suites failed")
		if nfail == 0:
			print ("\033[92mSUCCESS\033[0m\n")
		else:
			print ("\033[93mFAIL\033[0m\n")
		
		cls.suites = list()
		return nfail == 0


def prepare_tests():

	suite = Suite("fork and execve")
	suite.add(Test('foo', err='msh: command not found'))
	suite.add(CompareTest('ls'))
	suite.add(CompareTest('ls -laF'))
	suite.add(CompareTest('ls -l -a -F'))
	suite.add(CompareTest('		ls         -l -a -F'))
	suite.add(CompareTest('				ls 		'))
	suite.add(CompareTest('  ls -l		-aF '))
	suite.add(Test(''))
	suite.add(Test(' '))
	suite.add(Test('		'))

	suite = Suite("builtins")
	suite.add(Test('exit', out="", err=""))
	suite.add(Test('echo It works', out="It works"))
	suite.add(Test('echo "Hello"', out="Hello"))
	suite.add(Test('echo "', out='"'))
	suite.add(Test('cd /usr/bin ; /bin/pwd', out='/usr/bin'))
	suite.add(Test('cd /usr ; cd bin ; /bin/pwd', out='/usr/bin'))
	suite.add(Test('cd ; /bin/pwd', out=os.getenv("HOME")))
	suite.add(Test('cd /usr/bin ; cd /tmp ; cd - ; /bin/pwd', out='/usr/bin'))
	suite.add(Test('cd /usr/bin /tmp', err="msh: cd: too many arguments"))

	suite = Suite("environment")
	suite.add(CompareTest('env'))
	suite.add(Test('env a b', err="msh: env: too many arguments"))
	suite.add(CustomTest('setenv FOO bar ; env', lambda out, err: out.count('FOO=bar') == 1))
	suite.add(CustomTest('setenv FOO bar ; /usr/bin/env', lambda out, err: out.count('FOO=bar') == 1))
	suite.add(CustomTest('setenv FOO bar ; unsetenv FOO ; env', lambda out, err: out.count('FOO=bar') == 0))
	suite.add(CustomTest('setenv FOO bar ; unsetenv FOO ; unsetenv FOO ; env', lambda out, err: out.count('FOO=bar') == 0))
	suite.add(CustomTest('setenv FOO bar ; unsetenv FOO ; /usr/bin/env', lambda out, err: out.count('FOO=bar') == 0))
	suite.add(CustomTest('setenv FOO bar ; setenv FOO baz ; env', lambda out, err: out.count('FOO=bar') == 0))
	suite.add(CustomTest('setenv FOO bar ; setenv FOO baz ; env', lambda out, err: out.count('FOO=') == 1))
	suite.add(CustomTest('setenv FOO bar ; setenv FOO baz ; env', lambda out, err: out.count('FOO=baz') == 1))
	suite.add(Test('setenv a b c', err="msh: setenv: too many arguments"))
	suite.add(Test("setenv PATH /bin:/usr/bin", "", ""))

	suite = Suite("variable expansion")
	suite.add(Test('setenv FOO bar ; echo $FOO', out="bar"));
	suite.add(Test('setenv FOO bar ; echo blabla-$FOO/hello', out="blabla-bar/hello"));
	suite.add(Test('echo $HOME', out=os.getenv("HOME")));
	suite.add(Test('echo ~', out=os.getenv("HOME")));
	suite.add(Test('echo ~/hello', out=f'{os.getenv("HOME")}/hello'));
	suite.add(Test('setenv FOO bar ; echo ~/$FOO', out=f'{os.getenv("HOME")}/bar'));

	suite = Suite("PATH management")
	suite.add(CompareTest('unsetenv PATH ; setenv PATH "/bin:/usr/bin" ; ls', '"PATH=/bin:/usr/bin" ls'))
	suite.add(Test('unsetenv PATH ; ls', err="msh: command not found"))
	suite.add(CompareTest('unsetenv PATH ; /bin/ls', "ls"))


if __name__ == "__main__":
	if len(sys.argv) == 2:
		sys.chdir(sys.argv[1])
	if len(sys.argv) > 2 or not os.path.exists("./minishell"):
		sys.exit(f"Usage: {__file__} <path-to-project-directory>")

	prepare_tests()
	Suite.run_suites()
