#include "libft.h"
#include "job_control_42.h"

int		mark_process_status(t_job *first_job, pid_t pid, int status)
{
	t_job		*job;
	t_process	*proc;

	if (pid > 0)
	{
		job = first_job;
		while (job)
		{
			proc = job->first_process;
			while (proc)
			{
				proc->status = status;
				if (WIFSTOPPED(status))
					proc->stopped = true;
				else
				{
					proc->completed = true;
					if (WIFSIGNALED(status))
					{
						ft_putstr_fd("Job '", STDERR_FILENO);
						ft_putstr("'terminated by signal: ", STDERR_FILENO);
						ft_putnbr_fd(WTERMSIG(proc->status));
						ft_putchar('\n');
					}
				}
				proc = proc->next;
			}
			job = job->next;
		}
		return (0);
	}
	else if (pid == 0)
		return (WAITPID_ERROR);
	else
	{
		ft_putendl_fd("Waitpid Weird F*cking Error", STDERR_FILENO);
		return (WAITPID_ERROR);
	}
}
